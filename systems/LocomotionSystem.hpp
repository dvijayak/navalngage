#ifndef LocomotionSystem_HPP
#define LocomotionSystem_HPP

#include "ISystem.hpp"

class GameObjectFactory;

class LocomotionSystem
	: virtual public ISystem
{
public:
	LocomotionSystem ();
	~LocomotionSystem ();

	/// ISystem
	virtual void Update (size_t dt, GameObjectFactory const& factory);

private:
};

#endif