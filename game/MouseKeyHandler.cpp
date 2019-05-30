#include "MouseKeyHandler.hpp"

#include "GameObject.hpp"
#include "GameObjectFactory.hpp"

#include "SpeedAction.hpp"
#include "DirectionAction.hpp"
#include "RotateAction.hpp"
#include "CameraZoomAction.hpp"
#include "CameraFollowAction.hpp"

#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "BodyComponent.hpp"
#include "CameraComponent.hpp"

#include "MathUtil.hpp"

const int WHEEL_FACTOR = 5;

std::unique_ptr<MouseKeyHandler> MouseKeyHandler::s_pInstance;

MouseKeyHandler& MouseKeyHandler::Instance ()
{
	if (!s_pInstance)
	{		
		s_pInstance = std::unique_ptr<MouseKeyHandler>(new MouseKeyHandler());
	}

	return *s_pInstance;
}

void MouseKeyHandler::Destroy ()
{}

MouseKeyHandler::MouseKeyHandler ()
{}

bool MouseKeyHandler::TranslateToAction (SDL_Event const& event, GameObjectFactory const& factory, IEventHandler::ResultType& result)
{
	size_t before = result.size();

	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
	{
		int key = event.key.keysym.sym;

		if (event.type == SDL_KEYUP) // Key is released
		{
			// Untrack the key if it was held/pressed before
			KeyTrackerType::iterator it = m_keyTracker.find(key);
			if (it != m_keyTracker.end())
			{
				m_keyTracker.erase(it);
			}

			HandleKeyReleased(key, factory, result);
		}
		else // Key is pressed
		{
			bool bTrackKey(true); // track whether this key is being held/pressed

			HandleKeyPressed(key, factory, result, bTrackKey);

			if (bTrackKey)
			{
				m_keyTracker.insert(key);
			}
		}
	}
	else if (event.type == SDL_MOUSEWHEEL)
	{
		// Camera zooming
		GameObject* pCamera = factory.Resolve(GameObjectFactory::Suids::Camera1);
		if (pCamera)
		{
			std::unique_ptr<CameraZoomAction> p(new CameraZoomAction());
			p->SetCamera(pCamera);
			p->SetZoom(event.wheel.y * WHEEL_FACTOR);
			p->SetIncremental(true);
			result.push_back(std::move(p));
		}
	}

	return result.size() != before;
}

bool MouseKeyHandler::TranslateToActionPerFrame (GameObjectFactory const& factory, IEventHandler::ResultType& result)
{
	size_t before = result.size();

	for (auto const key : m_keyTracker)
	{
		if (KeyIsBeingHeld(key))
		{
			HandleKeyHeld(key, factory, result);
		}
	}

	return result.size() != before;
}

void MouseKeyHandler::HandleKeyPressed (int key, GameObjectFactory const& factory, IEventHandler::ResultType& result, bool& bTrackKey)
{
	GameObject* pCamera = factory.Resolve(GameObjectFactory::Suids::Camera1);
	
	switch (key)
	{
		// Change camera pan direction
		case SDLK_UP:
		case SDLK_LEFT:
		case SDLK_RIGHT:
		case SDLK_DOWN:
		{
			std::unique_ptr<DirectionAction> p(new DirectionAction());
			p->SetSource(pCamera);
			float x, y;
			switch (key)
			{
				case SDLK_UP:
					x = 0;
					y = 1;
					break;
				case SDLK_LEFT:
					x = -1;
					y = 0;
					break;
				case SDLK_RIGHT:
					x = 1;
					y = 0;
					break;
				case SDLK_DOWN:
					x = 0;
					y = -1;
					break;
				default:
					assert(false); // should never reach here
			}
			p->SetDirection(VectorF(x, y));
			result.push_back(std::move(p));
			break;
		}
		// Camera follow/unfollow target
		case SDLK_f:
		case SDLK_g:
		{

			GameObject* pFollowTarget(0); // 0 => unfollow
			if (key == SDLK_f)
				pFollowTarget = factory.Resolve(GameObjectFactory::Suids::Player1);
			std::unique_ptr<CameraFollowAction> p(new CameraFollowAction());
			p->SetCamera(pCamera);
			p->SetTarget(pFollowTarget);
			result.push_back(std::move(p));

			bTrackKey = false;
			break;
		}
	}
}

void MouseKeyHandler::HandleKeyHeld (int key, GameObjectFactory const& factory, IEventHandler::ResultType& result)
{
	switch (key)
	{
		// Player movement
		case SDLK_w:
		case SDLK_a:
		case SDLK_s:
		case SDLK_d:
		{
			GameObject* pPlayer = factory.Resolve(GameObjectFactory::Suids::Player1);
			if (pPlayer)
			{
				if (key == SDLK_w || key == SDLK_s)
				{
					float const inc = 1;
					std::unique_ptr<SpeedAction> p(new SpeedAction());
					p->SetSource(pPlayer);
					p->SetChangeType(SpeedAction::ADJUST);
					if (key == SDLK_w)
					{
						p->SetSpeed(inc);
					}
					else
					{
						p->SetSpeed(-inc);
					}
					result.push_back(std::move(p));
				}
				else if (key == SDLK_a || key == SDLK_d)
				{
					float const inc = MathUtil::DegreesToRadians(3);
					std::unique_ptr<RotateAction> p(new RotateAction());
					p->SetSource(pPlayer);
					if (key == SDLK_a) // counter-clockwise
					{
						p->SetAngle(inc);
					}
					else // clockwise
					{
						p->SetAngle(-inc);
					}
					result.push_back(std::move(p));
				}
			}
			break;
		}
		// Camera panning at a constant speed
		case SDLK_UP:
		case SDLK_LEFT:
		case SDLK_DOWN:
		case SDLK_RIGHT:
		{
			GameObject* pCamera = factory.Resolve(GameObjectFactory::Suids::Camera1);
			if (pCamera)
			{
				std::unique_ptr<SpeedAction> p(new SpeedAction());
				p->SetSource(pCamera);
				p->SetSpeed(100);
				result.push_back(std::move(p));
			}
			break;
		}
		// Camera zooming
		case SDLK_KP_PLUS:
		case SDLK_KP_MINUS:
		{
			GameObject* pCamera = factory.Resolve(GameObjectFactory::Suids::Camera1);
			if (pCamera)
			{
				std::unique_ptr<CameraZoomAction> p(new CameraZoomAction());
				p->SetCamera(pCamera);
				float amount = 1;
				if (key == SDLK_KP_MINUS)
					amount = -amount;
				p->SetZoom(amount);
				p->SetIncremental(true);
				result.push_back(std::move(p));
			}
			break;
		}
		// TEST: Projectile concept
		case SDLK_z:
		{
			// Spawn projectile in movement direction
			GameObject* pGo = factory.Resolve(GameObjectFactory::Suids::Player1);
			VectorF const& p = pGo->Get<PositionComponent>().GetPosition();
			GameObject& proj = const_cast<GameObjectFactory&>(factory).Create();
			proj.AddComponent(new PositionComponent());
			VectorF const& v = pGo->Get<MovementComponent>().GetDirection();
			proj.AddComponent(new MovementComponent(v.NormalizeCopy(), 100.0, 300.0));
			proj.AddComponent(new BodyComponent(PolygonF::CreateTriangle(
					PointF(p.GetX(), p.GetY()),
					PointF(p.GetX()+0.5, p.GetY()+0.5),
					PointF(p.GetX()-0.5, p.GetY()+0.5)
				)));
			break;
		}
	}
}

void MouseKeyHandler::HandleKeyReleased (int key, GameObjectFactory const& factory, IEventHandler::ResultType& result)
{
	switch (key)
	{
		// Stop panning the camera
		case SDLK_UP:
		case SDLK_LEFT:
		case SDLK_DOWN:
		case SDLK_RIGHT:
		{
			GameObject* pCamera = factory.Resolve(GameObjectFactory::Suids::Camera1);
			if (pCamera)
			{
				std::unique_ptr<SpeedAction> p(new SpeedAction());
				p->SetSource(pCamera);
				p->SetSpeed(0);
				result.push_back(std::move(p));
			}
			break;
		}
	}
}