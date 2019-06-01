#include "LocomotionSystem.hpp"

#include "global.hpp"

#include "GameObjectFactory.hpp"

#include "PositionComponent.hpp"
#include "SpeedComponent.hpp"
#include "RotationComponent.hpp"
#include "MountComponent.hpp"

#include "VectorF.hpp"

LocomotionSystem::LocomotionSystem ()
{}

LocomotionSystem::~LocomotionSystem ()
{}

void LocomotionSystem::Update (size_t dt, GameObjectFactory & factory)
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
		// CANIMPROVE: Terminate early if the theta + speed haven't changed since the last time...although this is a generic improvement for all Components to cache their previous value...also, we should profile and see if this will REALLY give us the benefit compared to the memory cost of cacheing every GO's component's values
		float theta = pGo->Get<RotationComponent>().GetRotationAngle();
		float speed = pGo->Get<SpeedComponent>().GetSpeed();
		VectorF vel = VectorF(1, 0).Rotate(theta) * speed; // the unit vector 1,0 is 0 degrees on the unit circle, so we just need to rotate this vector to obtain the desired direction

		// We know velocity and elapsed time, we need to find displacement
		// d = v * t
		// Add position and displacement vectors to get the new position
		// TODO: Do world bounds check so that object doesn't move out of the world
		VectorF & pos = pGo->Get<PositionComponent>().GetPosition();
		pos += vel * (float(dt)/1000.0); // dt is in ms, v is in m/s

		// console("{}: {}", *pGo, pGo->Get<CPosition>());

		// Update linked objects
		// CANIMPROVE: Might be good to be a generic ISystem pure virtual function to be overridden
		if (pGo->Has<MountComponent>())
		{
			for (auto const suid : pGo->Get<MountComponent>().GetMountedObjs())
			{
				auto pGo = factory.Resolve(suid);
				if (pGo && pGo->Has<PositionComponent>())
				{
					pGo->Get<PositionComponent>().SetPosition(pos);
				}
			}
		}
	}
}