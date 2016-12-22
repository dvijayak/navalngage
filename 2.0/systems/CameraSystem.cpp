#include "CameraSystem.hpp"

#include "global.hpp"
#include "GameObjectFactory.hpp"

#include "PositionComponent.hpp"
#include "CameraComponent.hpp"

CameraSystem::CameraSystem ()
{}

CameraSystem::~CameraSystem ()
{}

void CameraSystem::Update (size_t dt, GameObjectFactory const& factory)
{
	const auto filter = [] (GameObject const& go) { return 
		go.HasComponent<PositionComponent>() &&
		go.HasComponent<CameraComponent>();
	};
	for (auto& pGo : factory.ResolveObjects(filter))
	{
		CameraComponent* pCamera = pGo->GetComponent<CameraComponent>();
		pCamera->UpdateView();

		// Check if we want to follow an object
		if (pCamera->m_pFollowTarget)
		{
			assert(pCamera->m_pFollowTarget->HasComponent<PositionComponent>()); // we shouldn't attempt to follow an object that does not have position
			pGo->GetComponent<PositionComponent>()->SetPosition(pCamera->m_pFollowTarget->GetComponent<PositionComponent>()->GetPosition());
		}

		// Update the camera's view rectangle based on the camera's position in the world. The position is 
		// interpreted as the center of its view rectangle.
		VectorF const& pos = pGo->GetComponent<PositionComponent>()->GetPosition();
		pCamera->m_viewRectangle.x = pos.GetX() - pCamera->m_viewRectangle.width/2.0;
		pCamera->m_viewRectangle.y = pos.GetY() + pCamera->m_viewRectangle.height/2.0;
	}
}