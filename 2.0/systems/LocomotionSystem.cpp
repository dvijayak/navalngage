#include "LocomotionSystem.hpp"

#include "global.hpp"
#include "GameObjectFactory.hpp"

#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "RotationComponent.hpp"
#include "BodyComponent.hpp"

#include "MathUtil.hpp"

LocomotionSystem::LocomotionSystem ()
{}

LocomotionSystem::~LocomotionSystem ()
{}

void LocomotionSystem::Update (size_t dt, GameObjectFactory const& factory)
{
	const auto filter = [] (GameObject const& go) { return 
		go.Has<PositionComponent>() &&
		go.Has<MovementComponent>();
	};
	for (auto& pGo : factory.ResolveObjects(filter))
	{
		MovementComponent const& mov = pGo->Get<MovementComponent>();

		// Movement (velocity) affects Position
		// We know velocity and elapsed time, we need to find displacement
		// d = v * t
		// Add position and displacement vectors to get the new position
		// TODO: Do world bounds check so that object doesn't move out of the world
		VectorF vel = mov.GetVelocity();
		VectorF& pos = pGo->Get<PositionComponent>().GetPosition();
		pos += vel * (float(dt)/1000.0); // dt is in ms, v is in m/s

		// console(*pGo << ": " << pGo->Get<CPosition>() << ", " << pGo->Get<CMovement>());
	}
}