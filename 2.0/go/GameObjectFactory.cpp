#include "GameObjectFactory.hpp"

#include <cassert>

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
	for (auto& pGo : m_gameObjects)
	{
		delete pGo;
	}
}

GameObject& GameObjectFactory::Create ()
{
	GameObject* pGo = new GameObject();

	// TODO: Make thread-safe
	pGo->m_suid = s_nextAvailableSuid++;

	m_gameObjects.push_back(pGo);

	return *pGo;
}