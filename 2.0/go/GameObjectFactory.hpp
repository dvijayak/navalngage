#ifndef GameObjectFactory_HPP
#define GameObjectFactory_HPP

#include <map>

#include "GameObject.hpp"

class IGameObjectBuilder;

/// Singleton which constructs GOs and manages the lifetime thereof.
class GameObjectFactory
{
public:
	GameObjectFactory ();
	~GameObjectFactory ();

	/// Constructs a new empty game object. The caller must then add components.
	/// Synopsis:
	///    GameObject& go = GameObjectFactory::Instance().Create();
	///    go.AddComponent(new PositionComponent());
	///    // etc.
	GameObject& Create (bool bAdd=true);

	// Support builders for specific object/entity types
	// Example: ShipBuilder, CannonballBuilder
	GameObject& Create (IGameObjectBuilder&);

	bool Destroy (GOSuid);
	GameObject* Resolve (GOSuid);

	typedef std::map<GOSuid, GameObject*> GOContainerType;
	GOContainerType const& GetAllGameObjects () const { return m_gameObjects; }

private:
	void Add (GameObject*);

	GOContainerType m_gameObjects; // TODO: abstract away the collection implementation

	static bool s_bAlreadyCreated;

	static GOSuid s_nextAvailableSuid;
};

#endif