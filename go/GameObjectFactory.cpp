#include "GameObjectFactory.hpp"

#include <cassert>
#include <algorithm>

#include "Chrono.hpp"
#include "GameObjectBuilder.hpp"

bool GameObjectFactory::s_bAlreadyCreated = false;

GameObjectFactory::GameObjectFactory ()
{
	// Ensure singletonian creation
	assert(!s_bAlreadyCreated); 
	s_bAlreadyCreated = true;
}

GameObjectFactory::~GameObjectFactory ()
{
}

void GameObjectFactory::Add (GameObject* pGo, GOSuid id)
{
	assert(pGo);

	if (!id) // an id was not specified by the caller
	{
		// CANIMPROVE: might need to be concerned about potential multi-thread problems
		id = Chrono::GetTicksRelativeToStartup();
		while (!id || Resolve(id)) // it is possible to receive a value of 0 when computing tick count depending on the resolution thereof, so we handle this as well
		{
			++id;
		}
	}
	else
	{
		// If a desired ID was specified, it is better to assert
		// than to handle this silently and cause subtle bugs
		// later on.
		assert(!Resolve(id));
	}

	assert(id); // 0 is reserved, otherwise above logic won't work

	pGo->m_suid = id;

	// Finally, throw the new GO into our container
	m_gameObjects[pGo->m_suid] = std::unique_ptr<GameObject>(pGo);
}

GameObject& GameObjectFactory::Create (GOSuid id)
{
	GameObject* pGo = new GameObject();
	Add(pGo, id);
	assert(pGo);
	return *pGo;
}

GameObject& GameObjectFactory::Create (GameObjectBuilder& builder, GOSuid id)
{
	GameObject& go = Create(id);
	builder.GetResult(go);
	return go;
}

bool GameObjectFactory::Destroy (GOSuid id)
{
	auto it = m_gameObjects.find(id);
	if (it != m_gameObjects.end())
	{
		m_gameObjects.erase(it);
		return true;
	}

	return false;
}

GameObject* GameObjectFactory::Resolve (GOSuid id) const
{
	auto it = m_gameObjects.find(id);
	if (it != m_gameObjects.end())
	{
		assert(it->second); // we should never have a null GO in the factory
		return it->second.get();
	}

	return nullptr;
}

GameObjectFactory::GOResultListType GameObjectFactory::ResolveObjects (FilterType filter) const
{
	GOResultListType result;

	for (auto& p : m_gameObjects)
	{
		// p.first => GOSuid, p.second => GO pointer
		assert(p.second);
		if (filter(*(p.second)))
		{
			result.push_back(p.second.get());
		}
	}

	return result;
}
