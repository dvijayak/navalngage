#ifndef MovableBuilder_hpp
#define MovableBuilder_hpp

#include "GameObjectBuilder.hpp"
#include "VectorF.hpp"
#include "Color.hpp"
#include "Geometry.hpp"

class MovableBuilder
	: virtual public GameObjectBuilder
{
public:
	MovableBuilder ();
	virtual ~MovableBuilder ();

	/// GameObjectBuilder
	virtual void MakeDefault (); // Note: a body isn't created by default!

	virtual void AddPosition (float, float);
	virtual void AddPosition (VectorF const&);
	virtual void AddMovement (VectorF const&, float, float);
	virtual void AddBody (PolygonF const& poly, Uint32 color=Color::Green);
};

#endif