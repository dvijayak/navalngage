#include "GameObjectFactory.hpp"

GameObjectFactory* GameObjectFactory::s_pInstance = 0;
GOSuid GameObjectFactory::s_nextAvailableSuid = 1;

GameObjectFactory& GameObjectFactory::Instance ()
{
	if (!s_pInstance)
	{
		s_pInstance = new GameObjectFactory(); // TODO: Who will delete?
	}

	return *s_pInstance;
}

GameObjectFactory::GameObjectFactory ()
{}

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