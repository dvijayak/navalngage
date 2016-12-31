#include "MouseKeyHandler.hpp"

#include "GameObject.hpp"
#include "GameObjectFactory.hpp"

#include "SpeedAction.hpp"
#include "RotateAction.hpp"

#include "CameraComponent.hpp"

#include "MathUtil.hpp"

#include "global.hpp" // TOREMOVE

MouseKeyHandler* MouseKeyHandler::s_pInstance(0);

MouseKeyHandler& MouseKeyHandler::Instance ()
{
	if (!s_pInstance)
	{		
		s_pInstance = new MouseKeyHandler();
	}

	return *s_pInstance;
}

void MouseKeyHandler::Destroy ()
{
	if (s_pInstance)
	{
		delete s_pInstance;
	}
}

MouseKeyHandler::MouseKeyHandler ()
{}

bool MouseKeyHandler::TranslateToAction (SDL_Event const& event, GameObjectFactory const& factory, std::vector<Action*>& result)
{
	if (event.type == SDL_KEYDOWN)
	{
		int key = event.key.keysym.sym;
		switch (key)
		{
			case SDLK_w:
			case SDLK_a:
			case SDLK_s:
			case SDLK_d:
			{
				// TODO: Need better way to resolve certain key
				// objects rather than relying on brittle suids
				GameObject* pPlayer = factory.Resolve(2);
				if (pPlayer)
				{
					float inc = 1;
					if (key == SDLK_w || key == SDLK_s)
					{
						SpeedAction* p = new SpeedAction();
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
						result.push_back(p);
					}
					else if (key == SDLK_a || key == SDLK_d)
					{
						// TODO: Implement smooth rotation!
						inc = MathUtil::DegreesToRadians(3);
						RotateAction* p = new RotateAction();
						p->SetSource(pPlayer);
						if (key == SDLK_a) // counter-clockwise
						{
							p->SetAngle(inc);
						}
						else // clockwise
						{
							p->SetAngle(-inc);
						}
						result.push_back(p);
					}
				}
				break;
			}
			case SDLK_UP:
			case SDLK_LEFT:
			case SDLK_DOWN:
			case SDLK_RIGHT:
			{
				// TODO: Implement constant speed camera panning
			}
		}

		// Player object

		// TODO: super hacky control handling follows; this is of course to be improved

		// GameObject* pGo(0);
		// switch (event.key.keysym.sym)
		// {
		// 	case SDLK_w:
		// 	case SDLK_a:
		// 	case SDLK_s:
		// 	case SDLK_d:
		// 		pGo = m_factory.Resolve(2);
		// 		break;
		// 	case SDLK_UP:
		// 	case SDLK_LEFT:
		// 	case SDLK_DOWN:
		// 	case SDLK_RIGHT:
		// 		pGo = m_pCamera;
		// 		break;
		// 	case SDLK_f:
		// 		m_pCamera->GetComponent<CameraComponent>()->Follow(m_factory.Resolve(2));
		// 		break;
		// 	case SDLK_g:
		// 		m_pCamera->GetComponent<CameraComponent>()->UnFollow();
		// 		break;
		// 	case SDLK_z:
		// 	{
		// 		// TEST: Projectile concept
		// 		// Spawn projectile in movement direction
		// 		GameObject* pGo = m_factory.Resolve(2);
		// 		VectorF const& p = pGo->GetComponent<PositionComponent>()->GetPosition();
		// 		VectorF const& v = pGo->GetComponent<MovementComponent>()->GetVelocity();
		// 		GameObject& proj = m_factory.Create();
		// 		proj.AddComponent(new PositionComponent());
		// 		proj.AddComponent(new MovementComponent(v.NormalizeCopy() * 250.0, 300.0));
		// 		proj.AddComponent(new BodyComponent(PolygonF::CreateTriangle(
		// 				PointF(p.GetX(), p.GetY()),
		// 				PointF(p.GetX()+10.0, p.GetY()+10.0),
		// 				PointF(p.GetX()-10.0, p.GetY()+10.0)
		// 			)));
		// 		break;
		// 	}
		// 	case SDLK_x:
		// 		AddAction a;
		// 		a.SetSource(m_factory.Resolve(2));
		// 		a.SetTarget(m_pCamera);
		// 		a.SetFactor(10);
		// 		a.Perform();
		// }
		// if (!pGo) continue;

		// const float inc = 5;
		// VectorF& vel = pGo->GetComponent<MovementComponent>()->GetVelocity();
		// switch (event.key.keysym.sym)
		// {
		// 	case SDLK_w:
		// 	case SDLK_UP:
		// 	{
		// 		vel.SetY(vel.GetY() + inc);
		// 		break;
		// 	}
		// 	case SDLK_a:
		// 	case SDLK_LEFT:
		// 	{
		// 		vel.SetX(vel.GetX() - inc);
		// 		break;
		// 	}
		// 	case SDLK_s:
		// 	case SDLK_DOWN:
		// 	{
		// 		vel.SetY(vel.GetY() - inc);
		// 		break;
		// 	}
		// 	case SDLK_d:
		// 	case SDLK_RIGHT:
		// 	{
		// 		vel.SetX(vel.GetX() + inc);
		// 		break;
		// 	}
		// }
	}
	else if (event.type == SDL_MOUSEWHEEL)
	{
		// TODO: Implement camera zoom action
		float inc = event.wheel.y;
		factory.Resolve(1)->GetComponent<CameraComponent>()->Zoom(inc);
	}

	return !result.empty();
}