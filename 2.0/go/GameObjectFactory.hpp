#ifndef GameObjectFactory_HPP
#define GameObjectFactory_HPP

#include <map>
#include <vector>
#include <functional>

#include "GameObject.hpp"

class GameObjectBuilder;

/// Singleton which constructs GOs and manages the lifetime thereof.
class GameObjectFactory
{
public:
	GameObjectFactory ();
	~GameObjectFactory ();

	typedef std::map<GOSuid, GameObject*> GOContainerType;

	/// Constructs a new empty game object. The caller must then add components.
	/// A suid may be specified or the factory will figure out
	/// a value if 0 is passed (default value).
	/// Synopsis:
	///    GameObject& go = GameObjectFactory::Instance().Create();
	///    go.AddComponent(new PositionComponent());
	///    // etc.
	GameObject& Create (GOSuid=0);

	// Support builders for specific object/entity types
	// Example: ShipBuilder, CannonballBuilder
	GameObject& Create (GameObjectBuilder&, GOSuid=0);

	bool Destroy (GOSuid);
	GameObject* Resolve (GOSuid) const;

	typedef std::vector<GameObject*> GOResultListType; // TODO: should be vector of GO references
	typedef std::function<bool(GameObject const&)> FilterType;
	GOResultListType ResolveObjects (FilterType filter=[] (GameObject const&) { return true; }) const; // Move semantics should kick in

	/// IDs for core objects
	enum Suids
	{
		Camera1 = 1,
		Player1 = 2
	};

private:
	/// Inserts the GO into the factory GO container
	void Add (GameObject*, GOSuid=0);

	GOContainerType m_gameObjects; // TODO: abstract away the collection implementation

	static bool s_bAlreadyCreated;

	static GOSuid s_nextAvailableSuid;
};

#endif