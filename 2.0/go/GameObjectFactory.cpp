#include "GameObjectFactory.hpp"

#include <cassert>
#include <algorithm>

#include "IGameObjectBuilder.hpp"

bool GameObjectFactory::s_bAlreadyCreated = false;
GOSuid GameObjectFactory::s_nextAvailableSuid = 1;

GameObjectFactory::GameObjectFactory ()
{
	// Ensure singletonian creation
	assert(!s_bAlreadyCreated); 
	s_bAlreadyCreated = true;
}

GameObjectFactory::~GameObjectFactory ()
{
	// Simply destroy all extant GOs
	for (auto& p : m_gameObjects)
	{
		delete p.second;
	}
}

void GameObjectFactory::Add (GameObject* pGo)
{
	assert(pGo);

	// CANIMPROVE: Make thread-safe
	pGo->m_suid = s_nextAvailableSuid++;

	// First, destroy an existing GO with the same id if it exists
	// Note: this situation should never arise but you never know
	Destroy(pGo->m_suid);

	// Then, throw the new GO into our container
	m_gameObjects[pGo->m_suid] = pGo;
}

GameObject& GameObjectFactory::Create (bool bAdd)
{
	GameObject* pGo = new GameObject();
	if (bAdd)
	{
		Add(pGo);
	}
	return *pGo;
}

GameObject& GameObjectFactory::Create (IGameObjectBuilder& builder)
{
	GameObject* pGo = builder.GetResult();
	assert(pGo);
	Add(pGo);
	return *pGo;
}

bool GameObjectFactory::Destroy (GOSuid id)
{
	auto it = m_gameObjects.find(id);
	if (it != m_gameObjects.end())
	{
		delete it->second;
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
		return it->second;
	}

	return 0;
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
			result.push_back(p.second);
		}
	}

	return result;
}
