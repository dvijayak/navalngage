#include "LocomotionSystem.hpp"

#include "global.hpp"
#include "GameObjectFactory.hpp"

#include "PositionComponent.hpp"
#include "MovementComponent.hpp"

LocomotionSystem::LocomotionSystem ()
{}

LocomotionSystem::~LocomotionSystem ()
{}

void LocomotionSystem::Update (size_t dt, GameObjectFactory const& factory)
{
	auto filter = [] (GameObject const& go) { return 
		go.HasComponent<PositionComponent>() &&
		go.HasComponent<MovementComponent>();
	};
	for (auto& pGo : factory.ResolveObjects(filter))
	{
		// TODO: Mass affects Rotation
		// TODO: Mass affects Movement
		VectorF& velMod = pGo->GetComponent<MovementComponent>()->GetVelocityMod();
		// TODO: Rotation affects Movement

		// Movement (velocity) affects Position
		// We know velocity and elapsed time, we need to find displacement
		// d = v * t
		// Add position and displacement vectors to get the new position
		VectorF& posMod = pGo->GetComponent<PositionComponent>()->GetPositionMod();
		posMod += velMod * (dt/1000.0); // dt is in ms, v is in m/s
	}
}