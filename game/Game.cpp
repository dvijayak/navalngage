#include "Game.hpp"

#include "global.hpp"

#include "Color.hpp"
#include "Chrono.hpp"

#include "Geometry.hpp"
#include "VectorF.hpp"
#include "MathUtil.hpp"

#include "IEventHandler.hpp"

#include "GameObjectFactory.hpp"
#include "MovableBuilder.hpp"
#include "ShipBuilder.hpp"

#include "CameraComponent.hpp"
#include "PositionComponent.hpp"
#include "RelativePositionComponent.hpp"
#include "RotationComponent.hpp"
#include "BodyComponent.hpp"
#include "WeaponComponent.hpp"
#include "CannonWeapon.hpp"
#include "ShipComponent.hpp"
#include "MountComponent.hpp"

#include "Action.hpp"
#include "MouseKeyHandler.hpp"
#include "TimerManager.hpp"

#include <algorithm>

constexpr size_t MAX_FPS = 240;
constexpr size_t MIN_FPS = 15;

// For now, specify our world dimensions here. We'll later refactor this 
// into a better place in the code
constexpr float WORLD_RATIO = 1.6; // 16:10
constexpr float WORLD_WIDTH  = WORLD_RATIO * 4000;
constexpr float WORLD_HEIGHT = WORLD_RATIO * 3000;

Game::Game ()
	: m_targetFrameRate(60)
	, m_fixedUpdateTimeStep(1000/m_targetFrameRate)
	, m_pRenderer(0)
	, m_world(WORLD_WIDTH, WORLD_HEIGHT) // origin = (0,0)
	, m_pCamera(0)
{
	console("{}", m_world.GetRect());
	
	// Construct the camera
	PointF cameraPos = m_world.GetOrigin(); // for now, position camera at the center of the world
	MovableBuilder mb;
	mb.AddPosition(cameraPos.x, cameraPos.y);
	mb.AddSpeed(0, 100);
	mb.AddRotation(0);
	m_pCamera = &(m_factory.Create(mb, GameObjectFactory::Suids::Camera1));
	m_pCamera->AddComponent(new CameraComponent(&m_world, cameraPos.x, cameraPos.y));

	console("{}", *m_pCamera);
	console("{}", m_pCamera->Get<CCamera>());
}

Game::~Game ()
{
	// Destroy relevant singletons/managers
	MouseKeyHandler::Destroy();
}


int Game::Run ()
{
	//// Create some test objects ////

	ShipBuilder sb;
	sb.MakeDefault();
	// sb.AddPosition(15, -25);
	sb.AddBody(PolygonF::CreateNPolygon({
		PointF(0, 3),
		PointF(1, 2),
		PointF(0.6, -1.5),
		PointF(-0.6, -1.5),
		PointF(-1, 2),
	}), Color::Orange);
	GameObject& ship1 = m_factory.Create(sb);
	console("{}", ship1);

	sb.Reset();
	sb.MakeDefault();
	sb.AddShip(ShipComponent::FRIGATE);
	sb.AddPosition(-15, -25);
	sb.AddBody(PolygonF::CreateNPolygon({
		PointF(0, 6),
		PointF(2.3, 1),
		PointF(1.6, -3),
		PointF(-1.6, -3),
		PointF(-2.3, 1)
	}), Color::Red);
	GameObject& ship2 = m_factory.Create(sb, GameObjectFactory::Suids::Player1);
	console("{}", ship2);

	sb.Reset();
	sb.MakeDefault();
	sb.AddShip(ShipComponent::MANOFWAR);
	sb.AddPosition(-50, -25);
	sb.AddBody(PolygonF::CreateNPolygon({
		PointF(0, 11),
		PointF(4, 4),
		PointF(4, -7),
		PointF(2, -10),
		PointF(-2, -10),
		PointF(-4, -7),
		PointF(-4, 4)
	}), Color::Purple);
	GameObject& ship3 = m_factory.Create(sb);
	console("{}", ship3);

	// Test weapon
	MovableBuilder mb;
	mb.MakeDefault();
	{
		std::vector<float> c{0, -2, 1.5, 1, 0.5, 10};
		std::transform(c.begin(), c.end(), c.begin(), [](float f) -> float { return f/2; });
		PointF p1 (-c[4], c[1]);
		PointF p2 (p1.x - c[3], p1.y + c[2]);
		PointF p3 (p2.x, p2.y + c[2]);
		PointF p4 (p1.x, p3.y + c[2]);
		PointF p5 (p1.x, p4.y + c[5]);
		PointF p6 (p1.x + c[3], p5.y);
		PointF p7 (p6.x, p6.y - c[5]);
		PointF p8 (p7.x + c[3], p7.y - c[2]);
		PointF p9 (p8.x, p8.y - c[2]);
		PointF p10(p6.x, p1.y);

		mb.AddBody(PolygonF::CreateNPolygon({
			p1, p2, p3, p4, p5, p6, p7, p8, p9, p10
		}), Color::Yellow);
	}
	GameObject & cannon1 = m_factory.Create(mb, GameObjectFactory::Suids::Cannon1);
	cannon1.AddComponent(new WeaponComponent(std::unique_ptr<Weapon>(new CannonWeapon(75, 1, 100))));
	{
		// Establish a link between this cannon and the player ship
		cannon1.AddComponent(new RelativePositionComponent(0, 0));
		GameObject * pPlayerShip = m_factory.Resolve(GameObjectFactory::Suids::Player1);
		assert(pPlayerShip);
		std::vector<GOSuid> mountedObjs{cannon1.GetSuid()};
		pPlayerShip->AddComponent(new MountComponent(mountedObjs));
		console("{}", pPlayerShip->Get<MountComponent>());
	}
	console("{}", cannon1);

	//// Game loop ////
	
	int rc = GameErrorCode::OK;

	// Used in computing time-step
	size_t previous = Chrono::GetTicks();
	size_t current = 0;
	size_t elapsed = 0;
	size_t lag = 0;

	// Spin away!
	while (true)
	{
		// Calculate elapsed time-step
		// (Courtesy of Game Programming Patterns by Robert Nystrom)
		current = Chrono::GetTicks();
		elapsed = current - previous;
		lag += elapsed;
		previous = current;
		// console("elapsed = {}, lag = {}",  elapsed, lag);
	
		// Process all events in the SDL event queue; this is also the point at which the game loop can be exited
		if (ProcessEvents()) break;

		// Update all systems using a series of fixed time-steps
		while (lag >= m_fixedUpdateTimeStep)
		{
			for (auto& p : m_systems) // order of iteration is significant!
			{
				assert(p.second); // system pointer is expected to be valid
				p.second->Update(m_fixedUpdateTimeStep, m_factory);
			}

			lag -= m_fixedUpdateTimeStep;
		}

		// Render the game using the normalized lag
		DrawWorld(float(lag)/float(m_fixedUpdateTimeStep));

		// Consider sleeping a bit after a cycle to save power/energy on the host platform
		// TODO: Make this a configurable setting
		SDL_Delay(1);
	}

	return rc;
}

void Game::SetTargetFrameRate (size_t fps)
{
	if (fps > MAX_FPS)
	{
		fps = MAX_FPS;
	}
	else if (fps < MIN_FPS)
	{
		fps = MIN_FPS;
	}

	m_targetFrameRate = fps;
	m_fixedUpdateTimeStep = m_targetFrameRate/1000;
}

bool Game::RegisterSystem (ISystem* pSystem, int order)
{
	if (!pSystem)
	{
		return false;
	}

	bool rc = true;

	switch (order)
	{
		case SystemUpdateOrder::FIRST:
		{
			// Make this system the new foremost system to be run
			m_systems.insert(m_systems.begin(), std::make_pair(order, std::unique_ptr<ISystem>(pSystem)));		
			break;
		}
		case SystemUpdateOrder::LAST:
		{
			// Make this system the new last-most system to be run
			m_systems.push_back(std::make_pair(order, std::unique_ptr<ISystem>(pSystem)));		
			break;
		}
		case SystemUpdateOrder::MIDDLE:
		{
			// We don't care about where this system is inserted so long as it is
			// done so after the last FIRST system and before the first LAST system.
			// Just insert before the first LAST system if such a system exists
			// and if not, simply append.
			for (SystemListType::iterator it = m_systems.begin();; ++it)
			{
				// first => order, second => system pointer
				if (it == m_systems.end() || it->first == SystemUpdateOrder::LAST)
				{
					m_systems.insert(it, std::make_pair(order, std::unique_ptr<ISystem>(pSystem)));				
					break;
				}
			}

			break;
		}
		default:
		{
			rc = false;
		}
	}

	return rc;
}

bool Game::ProcessEvents ()
{
	static SDL_Event event; // watch out for thread-safety issues with static storage - currently should be fine since this function is only ever called on the main thread
	IEventHandler::ResultType actions;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
		{
			return true;
		}		

		switch (event.type)
		{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEWHEEL:
				MouseKeyHandler::Instance().TranslateToAction(event, m_factory, actions);
				break;

			case SDL_USEREVENT:
			{
				// TODO: Assume it's always a TIMEOUT for now, but not for too long
				assert(event.user.data1);
				auto wrapper = static_cast<TimerManager::Timeout *>(event.user.data1);
				assert(wrapper);
				wrapper->handler();
				delete wrapper; // SUPER IMPORTANT to be freed by calling code (us)!

				break;
			}
		}
	}

	// Smooth per-frame controls
	MouseKeyHandler::Instance().TranslateToActionPerFrame(m_factory, actions);

	for (auto& pAction : actions)
	{
		if (pAction)
		{
			// TODO: serialize for playback, etc.
			pAction->Perform();
		}
	}

	return false; // in the normal case, we are NOT exiting the game loop
}

void Game::DrawWorld (float dt)
{
	// TODO: Use the normalized lag dt to produce a more accurate render

	/// 1. Background
	// m_pRenderer->FillScreenBackground();
	// m_pRenderer->FillScreenBackground(Color::Mix(0x2a, 0x4d, 0xbf));
	m_pRenderer->FillScreenBackground(Color::Mix(0x1c, 0x33, 0x7f));

	/// 2. Wireframe/Axes
	// Determine all lines which intersect the camera view rectangle.
	// Construct line segments out of these then draw them
	//
	// x   x   x   x   x   x   x
	// =   =   =   =   =   =   =
	// 4   5   6   7   8   9   10
	//
	// |   |   |   |   |   |   |
	// -------------------------  y = 3
	// |   |   |   |   |   |   |
	// ------CCCCCCCCCCCC-------  y = 2
	// |   | C |   |   |C  |   |
	// ------C----------C-------  y = 1
	// |   | C |   |   |C  |   |
	// ------CCCCCCCCCCCC-------  y = 0
	// |   |   |   |   |   |   |
	// -------------------------  y = -1
	// |   |   |   |   |   |   |
	// -------------------------  y = -2
	// |   |   |   |   |   |   |
	//
	// In the above example, note the line segments formed by lines which intersect
	// the view rectangle (y=2, y=1, y=0, x=6, x=7 and x=8).
	CameraComponent const& camera = m_pCamera->Get<CameraComponent>();

	// Sint32 mouseStateX = 0, mouseStateY = 0;
	// SDL_GetMouseState(&mouseStateX, &mouseStateY);
	// console("Mouse: {}, {}", mouseStateX, mouseStateY);	
	// Point2F mouse(mouseStateX, mouseStateY);
	// camera.ScreenToWorld(mouse);
	// console("{}", mouse);

	/// 3. Point of world origin
	PointF worldOrigin = m_world.GetOrigin();
	if (camera.Includes(worldOrigin))
	{
		camera.WorldToScreen(worldOrigin);
		m_pRenderer->DrawPoint(worldOrigin);
	}

	/// 4. World objects
	// Draw only drawable objects that are visible by the camera
	// For now, a drawable object is one that has a surface polygon via a BodyComponent
	for (auto const& pGo : m_factory.ResolveObjects( [] (GameObject const& go) { return go.Has<BodyComponent>() && go.Has<PositionComponent>(); } ))
	{
		float theta = pGo->Has<RotationComponent>() ? pGo->Get<CRotation>().GetRotationAngle() : MathUtil::DegreesToRadians(90);

		// Access the object's surface polygon and color
		BodyComponent const& body = pGo->Get<BodyComponent>();
		PolygonF p = body.ComputeSurfaceWorld(pGo->Get<PositionComponent>().GetPosition(), theta);
		Uint32 color = body.GetSurfaceColor();

		std::vector<LineSegmentF> edges;
		p.ComputeEdges(edges);
		for (auto & edge : edges)
		{
			auto result = camera.ClipToViewport(edge);
			if (result == ClippingTestResult::TRIVIAL_REJECT)
			{
				continue;
			}

			// Transform clipped edge to screen space
			camera.WorldToScreen(edge.start);
			camera.WorldToScreen(edge.end);

			// Draw away!
			m_pRenderer->DrawLine(edge, color);
		}
	}

	// Final step - send the frame buffer to the video device
	m_pRenderer->Render();
}