#ifndef CameraSystem_HPP
#define CameraSystem_HPP

#include "ISystem.hpp"

class GameObjectFactory;

class CameraSystem
	: virtual public ISystem
{
public:
	CameraSystem ();
	~CameraSystem ();

	/// ISystem
	virtual void Update (size_t dt, GameObjectFactory const& factory);

private:
};

#endif