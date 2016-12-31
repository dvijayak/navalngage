#ifndef ShipBuilder_HPP
#define ShipBuilder_HPP

#include "IGameObjectBuilder.hpp"
#include "VectorF.hpp"
#include "Color.hpp"
#include "Geometry.hpp"

class GameObject;
class GameObjectFactory;

// TODO: Builders should be able to inherit from other builders. Implement a
// LocomotionBuilder which provides methods for constructing the position, movement
// and rotation (and maybe mass as well?) components.
class ShipBuilder
	: virtual public IGameObjectBuilder
{
public:
	// TODO: Figure a way to avoid needing to pass a GOFactory just to construct a ruddy GO
	ShipBuilder (GameObjectFactory&);
	~ShipBuilder ();

	/// IGameObjectBuilder
	virtual void MakeDefault (); // Note: a body isn't created by default!
	virtual GameObject* GetResult ();

	void AddPosition (float, float);
	void AddPosition (VectorF const&);
	void AddMovement (VectorF const&, float, float);
	void AddRotation (float, float);
	void AddShip (int ship_class);
	void AddMass (float);
	void AddBody (PolygonF const& poly, Uint32 color=Color::Green);

private:
	GameObject* m_pGo;

	// TODO: This is too restrictive. Figure out how to allow builder object reuse
	bool m_bConstructionCompleted;
};

#endif