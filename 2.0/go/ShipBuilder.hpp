#ifndef ShipBuilder_HPP
#define ShipBuilder_HPP

#include "IGameObjectBuilder.hpp"
#include "VectorF.hpp"

class GameObject;
class GameObjectFactory;

class ShipBuilder
	: virtual public IGameObjectBuilder
{
public:
	// TODO: Figure a way to avoid needing to pass a GOFactory just to construct a ruddy GO
	ShipBuilder (GameObjectFactory&);
	~ShipBuilder ();

	/// IGameObjectBuilder
	virtual void MakeDefault ();
	virtual GameObject* GetResult ();

	void AddPosition (float, float);
	void AddPosition (VectorF const&);
	void AddMovement (VectorF const&);
	void AddRotation (float);
	void AddShip (int ship_class);
	void AddMass (float);

private:
	GameObject* m_pGo;

	bool m_bConstructionCompleted;
};

#endif