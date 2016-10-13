#include "LocomotionSystem.hpp"

#include "global.hpp"
#include "GameObjectFactory.hpp"

LocomotionSystem::LocomotionSystem ()
{}

LocomotionSystem::~LocomotionSystem ()
{}

void LocomotionSystem::Update (size_t dt, GameObjectFactory const& factory)
{
	console("Running the locomotion system by " << dt << " ms.");
}