#include "GameObjectBuilder.hpp"

void GameObjectBuilder::GetResult (GameObject& go)
{
	for (auto& pComp : m_components)
	{
		go.AddComponent(pComp);
	}	
}

void GameObjectBuilder::Reset ()
{
	m_components.clear();
}