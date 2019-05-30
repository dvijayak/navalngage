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
		go.Has<PositionComponent>() &&
		go.Has<CameraComponent>();
	};
	for (auto& pGo : factory.ResolveObjects(filter))
	{
		CameraComponent& camera = pGo->Get<CameraComponent>();
		camera.UpdateView();

		// Check if we want to follow an object
		if (camera.m_pFollowTarget)
		{
			assert(camera.m_pFollowTarget->Has<PositionComponent>()); // we shouldn't attempt to follow an object that does not have position
			pGo->Get<PositionComponent>().SetPosition(camera.m_pFollowTarget->Get<PositionComponent>().GetPosition());
		}

		// Update the camera's view rectangle based on the camera's position in the world.
		// The position is interpreted as the center of its view rectangle.
		VectorF const& pos = pGo->Get<PositionComponent>().GetPosition();
		camera.m_viewRectangle.x = pos.GetX() - camera.m_viewRectangle.width/2.0;
		camera.m_viewRectangle.y = pos.GetY() + camera.m_viewRectangle.height/2.0;
	}
}