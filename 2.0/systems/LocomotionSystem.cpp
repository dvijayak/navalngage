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
	const auto filter = [] (GameObject const& go) { return 
		go.HasComponent<PositionComponent>() &&
		go.HasComponent<MovementComponent>();
	};
	for (auto& pGo : factory.ResolveObjects(filter))
	{
		MovementComponent* pMov = pGo->GetComponent<MovementComponent>();
		VectorF& vel = pMov->GetVelocity();

		// TODO: Mass affects velocity increment, but this needs to be handled at the command level, i.e. the point of state change

		// Scale the vector down to the speed upper bound
		float speed = vel.Norm();
		float maxSpeed = pMov->GetMaxSpeed();
		// TODO: Should mass affect max speed?
		if (speed > maxSpeed)
		{
			vel *= maxSpeed / speed;
		}

		// Movement (velocity) affects Position
		// We know velocity and elapsed time, we need to find displacement
		// d = v * t
		// Add position and displacement vectors to get the new position
		// TODO: Do world bounds check so that object doesn't move out of the world
		VectorF& pos = pGo->GetComponent<PositionComponent>()->GetPosition();
		pos += vel * (float(dt)/1000.0); // dt is in ms, v is in m/s

		// console(*pGo << " Vel = " << vel << ", New pos = " << pos);
	}
}