#ifndef GameObjectFactory_HPP
#define GameObjectFactory_HPP

#include <vector>

#include "GameObject.hpp"

/// Singleton which constructs GOs and manages the lifetime thereof.
class GameObjectFactory
{
public:
	~GameObjectFactory ();

	/// Constructs a new empty game object. The caller must then add components.
	/// Synopsis:
	///    GameObject& go = GameObjectFactory::Instance().Create();
	///    go.AddComponent(new PositionComponent());
	///    // etc.
	GameObject& Create ();

	// TODO: Support builders for specific object/entity types
	// Example: ShipBuilder, CannonballBuilder
	// GameObject& Create (GOBuilder* pBuilder);

	bool Destroy (GOSuid go_id);
	GameObject& Resolve (GOSuid go_id);

	static GameObjectFactory& Instance ();

private:
	std::vector<GameObject*> m_gameObjects; // TODO: abstract away the collection implementation

	GameObjectFactory ();
	static GameObjectFactory* s_pInstance;

	static GOSuid s_nextAvailableSuid;
};

#endif