#include "GameObject.hpp"

#include "global.hpp"

#include <cassert>
#include <ostream>

GameObject::GameObject ()
{
	// Should do nothing. Ideally, taken care of by builders.
}

GameObject::~GameObject ()
{}

bool GameObject::HasComponent (IComponent::Name const& name) const
{
	return m_components.find(name) != m_components.end();
}

IComponent* GameObject::GetComponent (IComponent::Name const& name) const
{
	ComponentContainer::const_iterator it = m_components.find(name);
	if (it != m_components.end())
	{
		return it->second.get();
	}

	return 0;
}

bool GameObject::AddComponent (IComponent* pComp)
{
	if (!pComp)
	{
		return false;
	}

	// First remove an existing component of the same name
	RemoveComponent(pComp);

	m_components[pComp->GetName()] = std::unique_ptr<IComponent>(pComp);

	return true;
}

bool GameObject::RemoveComponent (IComponent::Name const& name)
{
	ComponentContainer::iterator it = m_components.find(name);
	if (it != m_components.end())
	{
		trclog("{} Removing component [{}]", *this, name);
		m_components.erase(it);
		return true;
	}

	return false;
}

bool GameObject::RemoveComponent (IComponent* pComp)
{
	if (!pComp)
	{
		return false;
	}

	return RemoveComponent(pComp->GetName());
}

std::ostream& operator<< (std::ostream& os, GameObject const& go)
{
	os << "[";
	os << "GameObject #" << go.m_suid;
	// CANIMPROVE: Add support for printing components from here?
	// if (!go.m_components.empty())
	// {}
	os << "]";
	return os;
}

std::ostream& operator<< (std::ostream& os, GameObject const* pGo)
{
	if (!pGo)
	{
		os << "[GameObject (Null)]";
	}
	else
	{
		os << *pGo;
	}
	return os;
}