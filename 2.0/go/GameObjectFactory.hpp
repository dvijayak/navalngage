#ifndef GameObjectFactory_HPP
#define GameObjectFactory_HPP

#include <vector>

#include "GameObject.hpp"

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
	GameObject& Create ();

	// TODO: Support builders for specific object/entity types
	// Example: ShipBuilder, CannonballBuilder
	// GameObject& Create (GOBuilder* pBuilder);

	// TODO
	bool Destroy (GOSuid go_id);
	GameObject& Resolve (GOSuid go_id);

	std::vector<GameObject*> const& GetAllGameObjects () const { return m_gameObjects; }

private:
	std::vector<GameObject*> m_gameObjects; // TODO: abstract away the collection implementation

	static bool s_bAlreadyCreated;

	static GOSuid s_nextAvailableSuid;
};

#endif