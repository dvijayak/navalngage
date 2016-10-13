#ifndef IGameObjectBuilder_HPP
#define IGameObjectBuilder_HPP

#include "GameObject.hpp"

class IGameObjectBuilder
{
public:
	virtual ~IGameObjectBuilder () {}

	/// The GO is constructed using default settings as defined by the 
	/// implementing concrete builder
	virtual void MakeDefault () = 0;

	/// Get the constructed GO. The builder should NOT be used after this.
	/// CANIMPROVE: Can this lifetime be enforced other than via scoping and asserts?
	virtual GameObject* GetResult () = 0;
};

#endif