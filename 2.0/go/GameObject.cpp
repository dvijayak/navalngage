#include "GameObject.hpp"

#include <cassert>
#include <ostream>

GameObject::GameObject ()
{
	// Should do nothing. Ideally, taken care of by builders.
}

GameObject::~GameObject ()
{
	// Delete all extant components
	for (auto& el : m_components)
	{
		assert(el.second);
		delete el.second;
	}
}

bool GameObject::HasComponent (IComponent::Name const& name) const
{
	return m_components.find(name) != m_components.end();
}

IComponent* GameObject::GetComponent (IComponent::Name const& name) const
{
	ComponentContainer::const_iterator it = m_components.find(name);
	if (it != m_components.end())
	{
		return it->second;
	}

	return 0;
}

bool GameObject::AddComponent (IComponent* pComp)
{
	if (!pComp)
	{
		return false;
	}

	m_components[pComp->GetName()] = pComp;

	return true;
}

bool GameObject::RemoveComponent (IComponent::Name const& name)
{
	// TODO

	ComponentContainer::iterator it = m_components.find(name);
	if (it != m_components.end())
	{
		delete it->second;
		m_components.erase(it);
	}

	return false;
}

bool GameObject::RemoveComponent (IComponent* pComp)
{
	// TODO

	if (!pComp)
	{
		return false;
	}

	return false;
}

std::ostream& operator<< (std::ostream& os, GameObject const& go)
{
	os << "[";
	os << "GameObject #" << go.m_suid;
	if (!go.m_components.empty())
	{
		os << ": components = ";
		// TODO: Add ostream support for all components as well
	}
	os << "]";
	return os;
}