#ifndef GameObjectFactory_HPP
#define GameObjectFactory_HPP

#include <map>
#include <vector>
#include <functional>

#include "GameObject.hpp"

class IGameObjectBuilder;

/// Singleton which constructs GOs and manages the lifetime thereof.
class GameObjectFactory
{
public:
	GameObjectFactory ();
	~GameObjectFactory ();

	typedef std::map<GOSuid, GameObject*> GOContainerType;

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

	typedef std::vector<GameObject*> GOResultListType;
	typedef std::function<bool(GameObject const&)> FilterType;
	GOResultListType ResolveObjects (FilterType filter=[] (GameObject const&) { return true; }) const; // Move semantics should kick in

private:
	void Add (GameObject*);

	GOContainerType m_gameObjects; // TODO: abstract away the collection implementation

	static bool s_bAlreadyCreated;

	static GOSuid s_nextAvailableSuid;
};

#endif