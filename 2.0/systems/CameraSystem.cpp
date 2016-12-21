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

		// Update the camera's view rectangle based on the camera's position in the world
		// TODO: Do world bounds check so that camera doesn't move out of the world
		VectorF const& pos = pGo->GetComponent<PositionComponent>()->GetPosition();
		pCamera->m_viewRectangle.x = pos.GetX();
		pCamera->m_viewRectangle.y = pos.GetY();
	}
}