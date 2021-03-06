#include "MouseKeyHandler.hpp"

#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include "MovableBuilder.hpp"

#include "SpeedAction.hpp"
#include "DirectionAction.hpp"
#include "RotateAction.hpp"
#include "CameraZoomAction.hpp"
#include "CameraFollowAction.hpp"
#include "FireWeaponAction.hpp"

#include "PositionComponent.hpp"
#include "RotationComponent.hpp"
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
			float theta;
			switch (key)
			{
				case SDLK_UP:
					theta = MathUtil::DegreesToRadians(90);
					break;
				case SDLK_LEFT:
					theta = MathUtil::DegreesToRadians(180);
					break;
				case SDLK_RIGHT:
					theta = MathUtil::DegreesToRadians(0);
					break;
				case SDLK_DOWN:
					theta = MathUtil::DegreesToRadians(-90);
					break;
				default:
					assert(false); // should never reach here
			}
			p->SetDirection(theta);
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
		// TEST: Rotate mounted weapon
		case SDLK_q:
		case SDLK_e:
		{
			float const inc = MathUtil::DegreesToRadians(6);
			std::unique_ptr<RotateAction> p(new RotateAction());
			auto pGo = factory.Resolve(GameObjectFactory::Suids::Cannon1);
			if (!pGo)
			{
				break;
			}
			p->SetSource(pGo);
			if (key == SDLK_q) // counter-clockwise
			{
				p->SetAngle(inc);
			}
			else // clockwise
			{
				p->SetAngle(-inc);
			}
			result.push_back(std::move(p));
			break;
		}
		// TEST: Fire basic weapon
		case SDLK_z:
		{
			GameObject* pGo = factory.Resolve(GameObjectFactory::Suids::Cannon1); // TODO: remove when we start mounting weapons on ships
			if (!pGo)
			{
				break;
			}
			std::unique_ptr<FireWeaponAction> p(new FireWeaponAction());
			p->SetSource(pGo);
			result.push_back(std::move(p));
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