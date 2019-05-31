#ifndef ISystem_HPP
#define ISystem_HPP

class GameObjectFactory;

#include <stdlib.h> // for size_t

class ISystem
{
public:
	virtual ~ISystem () {};

	/// Update the state of game objects belonging to the given factory by 
	/// the dt time-step value.
	/// CANIMPROVE: Sending the entire factory seems overkill.
	virtual void Update (size_t dt, GameObjectFactory & factory) = 0;
};

#endif