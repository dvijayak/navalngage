#include "GameObjectFactory.hpp"

#include <cassert>

bool GameObjectFactory::s_bAlreadyCreated = false;
GOSuid GameObjectFactory::s_nextAvailableSuid = 1;

GameObjectFactory::GameObjectFactory ()
{
	assert(!s_bAlreadyCreated); // ensures singletonian creation
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