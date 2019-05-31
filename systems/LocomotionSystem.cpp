#include "LocomotionSystem.hpp"

#include "global.hpp"

#include "GameObjectFactory.hpp"

#include "PositionComponent.hpp"
#include "SpeedComponent.hpp"
#include "RotationComponent.hpp"

#include "VectorF.hpp"

LocomotionSystem::LocomotionSystem ()
{}

LocomotionSystem::~LocomotionSystem ()
{}

void LocomotionSystem::Update (size_t dt, GameObjectFactory const& factory)
{
	const auto filter = [] (GameObject const& go) { return 
		go.Has<PositionComponent>() &&
		go.Has<SpeedComponent>() &&
		go.Has<RotationComponent>();
	};
	for (auto& pGo : factory.ResolveObjects(filter))
	{
		// Movement (velocity) affects Position
		// It is computed from speed + rotation angle
		float theta = pGo->Get<RotationComponent>().GetRotationAngle();
		float speed = pGo->Get<SpeedComponent>().GetSpeed();
		VectorF vel = VectorF(1, 0).Rotate(theta) * speed; // the unit vector 1,0 is 0 degrees on the unit circle, so we just need to rotate this vector to obtain the desired direction

		// We know velocity and elapsed time, we need to find displacement
		// d = v * t
		// Add position and displacement vectors to get the new position
		// TODO: Do world bounds check so that object doesn't move out of the world
		VectorF& pos = pGo->Get<PositionComponent>().GetPosition();
		pos += vel * (float(dt)/1000.0); // dt is in ms, v is in m/s

		// console("{}: {}", *pGo, pGo->Get<CPosition>());
	}
}