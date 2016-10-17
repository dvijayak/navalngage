#include "Game.hpp"

#include "Color.hpp"

#include "Geometry.hpp"
#include "VectorF.hpp"

#include "GameObjectFactory.hpp"
#include "ShipBuilder.hpp"

#include "CameraComponent.hpp"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "BodyComponent.hpp"

constexpr size_t MAX_FPS = 240;
constexpr size_t MIN_FPS = 15;

// For now, specify our default world dimensions here. We'll later refactor this 
// into a better place in the code
constexpr float WORLD_RATIO = 1.6; // 16:10
constexpr float WORLD_WIDTH  = WORLD_RATIO * 4000;
constexpr float WORLD_HEIGHT = WORLD_RATIO * 3000;

Game::Game ()
	: m_targetFrameRate(60)
	, m_fixedUpdateTimeStep(1000/m_targetFrameRate)
	, m_pRenderer(0)
	, m_world(WORLD_WIDTH, WORLD_HEIGHT) // origin = (0,0)
{
	console(m_world.GetRect());
	
	// For now, position camera at the center of the world;
	PointF cameraPos = m_world.GetOrigin();
	cameraPos.y += 100;
	cameraPos.x -= 150;

	// Construct the camera
	m_pCamera = &(m_factory.Create());
	m_pCamera->AddComponent(new CameraComponent(&m_world, cameraPos.x, cameraPos.y));
	m_pCamera->AddComponent(new PositionComponent(cameraPos.x, cameraPos.y));
	m_pCamera->AddComponent(new MovementComponent(Vector2F(2, 2)));
	console(m_pCamera->GetComponent<CameraComponent>())
}

Game::~Game ()
{
	for (auto& p : m_systems)
	{
		delete p.second;
	}
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
			m_systems.insert(m_systems.begin(), std::make_pair(order, pSystem));		
			break;
		}
		case SystemUpdateOrder::LAST:
		{
			// Make this system the new last-most system to be run
			m_systems.push_back(std::make_pair(order, pSystem));		
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
					m_systems.insert(it, std::make_pair(order, pSystem));				
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

int Game::Run ()
{
	//// Create some test objects ////

	// TODO: implement the systems that involve Position, Movement and Body!!!
	// Recall: Movement affects Position, Position affects Body (surface polygon)!!

	ShipBuilder sb1(m_factory);
	sb1.MakeDefault();
	sb1.AddBody(PolygonF::CreateQuad(
		PointF(50, -25),
		PointF(150, -5),
		PointF(134, -123),
		PointF(67, -120)
	), Color::Orange);
	GameObject& ship1 = m_factory.Create(sb1);
	console(ship1);

	ShipBuilder sb2(m_factory);
	sb2.MakeDefault();
	sb2.AddBody(PolygonF::CreateNPolygon({
		PointF(-15, -100),
		PointF(13, -123),
		PointF(0, -134),
		PointF(-45, -113),
		PointF(-40, -100),
		PointF(-25, -95)
	}), Color::Red);
	GameObject& ship2 = m_factory.Create(sb2);
	console(ship2);

	ShipBuilder sb3(m_factory);
	sb3.MakeDefault();
	sb3.AddBody(PolygonF::CreateTriangle(
		PointF(40, -300),
		PointF(60, -365),
		PointF(12, -365)
	), Color::Cyan);
	GameObject& ship3 = m_factory.Create(sb3);
	console(ship3);

	//// Game loop ////

	bool bExit = false; // flag used to exit the game loop
	int rc = GameErrorCode::OK;

	// Used in computing time-step
	size_t previous = SDL_GetTicks();
	size_t current = 0;
	size_t elapsed = 0;
	size_t lag = 0;

	// Spin away!
	while (!bExit)
	{
		// Calculate elapsed time-step
		// (Courtesy of Game Programming Patterns by Robert Nystrom)
		current = SDL_GetTicks();
		elapsed = current - previous;
		lag += elapsed;
		previous = current;
		// console("elapsed = " << elapsed << "  lag = " << lag);

		// TODO: Process events in a clean manner
		SDL_Event event;
		while (!bExit && SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				bExit = true;
				break;
			}
			else if (event.type == SDL_KEYUP)
			{
				// if ((event.key.keysym.mod == KMOD_LCTRL || event.key.keysym.mod == KMOD_RCTRL)
				// 	&& event.key.keysym.sym == SDLK_q)
				if (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE)
				{
					bExit = true;
					break;
				}
			}
			else if (event.type == SDL_KEYDOWN)
			{
				float inc = 5;
				switch (event.key.keysym.sym)
				{
					case SDLK_w:
					{
						m_pCamera->GetComponent<CameraComponent>()->Pan(0, inc);
						break;
					}
					case SDLK_a:
					{
						m_pCamera->GetComponent<CameraComponent>()->Pan(-inc, 0);
						break;
					}
					case SDLK_s:
					{
						m_pCamera->GetComponent<CameraComponent>()->Pan(0, -inc);
						break;
					}
					case SDLK_d:
					{
						m_pCamera->GetComponent<CameraComponent>()->Pan(inc, 0);
						break;
					}
				}
			}
			else if (event.type == SDL_MOUSEWHEEL)
			{
				float inc = event.wheel.y;
				// m_pCamera->GetComponent<CameraComponent>()->Pan(inc, inc);
				m_pCamera->GetComponent<CameraComponent>()->Zoom(inc);
			}
		}
		if (bExit) break; // exit the game loop

		// Update all systems using a series of fixed time-steps
		while (lag >= m_fixedUpdateTimeStep)
		{
			for (auto& p : m_systems)
			{
				assert(p.second); // system pointer is expected to be valid
				p.second->Update(m_fixedUpdateTimeStep, m_factory);
			}

			lag -= m_fixedUpdateTimeStep;
		}


		// Render the game using the normalized lag
		DrawWorld(float(lag)/float(m_fixedUpdateTimeStep));

		// Consider sleeping a bit after a cycle to save power.energy on the host platform
		// TODO: Make this a configurable setting
		// For now, just disable it
		// SDL_Delay(m_fixedUpdateTimeStep);
	}

	return rc;
}

void Game::DrawWorld (float dt)
{
	m_pRenderer->FillScreenBackground();

	// Draw only drawable objects that are visible by the camera
	// For now, a drawable object is one that has a surface polygon via a BodyComponent
	size_t c_i = 0;
	for (auto const& pGo : m_factory.ResolveObjects( [] (GameObject const& go) { return go.HasComponent<BodyComponent>(); } ))
	{
		// Access the object's surface polygon and color
		BodyComponent* pBody = pGo->GetComponent<BodyComponent>();
		PolygonF const& p = pBody->GetSurface();
		Uint32 color = pBody->GetSurfaceColor();

		bool pass = false;
		for (auto const& v : p.vertices)
		{
			if (m_pCamera->GetComponent<CameraComponent>()->Includes(v))
			{
				pass = true;
				break; // For now, we draw a polygon if at least one of its vertices is included
			}
		}

		if (!pass)
		{
			continue;
		}

		// Apply transformations to all vertices
		PolygonF finalPoly(p);
		for (auto& v : finalPoly.vertices)
		{
			// v => normalized device coordinates
			m_pCamera->GetComponent<CameraComponent>()->WorldToScreen(v);			
		}

		// Draw away!
		m_pRenderer->DrawPolygon(finalPoly, color);

		c_i++;
	}

	// Final step - send the frame buffer to the video device
	m_pRenderer->Render();
}