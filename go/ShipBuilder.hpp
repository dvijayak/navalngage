#ifndef ShipBuilder_hpp
#define ShipBuilder_hpp

#include "MovableBuilder.hpp"
#include "VectorF.hpp"
#include "Color.hpp"
#include "Geometry.hpp"

class ShipBuilder
	: virtual public MovableBuilder
{
public:
	ShipBuilder ();
	virtual ~ShipBuilder ();

	/// GameObjectBuilder
	virtual void MakeDefault (); // Note: a body isn't created by default!

	virtual void AddShip (int ship_class);
	virtual void AddMass (float);
};

#endif