#ifndef GO_HPP
#define GO_HPP

#include <map>

#include "IComponent.hpp"

typedef int GOSuid;

/// Essentially, a collection of components, along with some other information.
/// Manages the lifecycle of its components.
class GameObject
{
public:
	~GameObject ();

	GOSuid GetSuid () const { return m_suid; };

	bool HasComponent (IComponent::Name const& name) const;
	template <class T> bool HasComponent () const;
	IComponent* GetComponent (IComponent::Name const& name) const;
	template <class T> T* GetComponent () const;

	bool AddComponent (IComponent* pComp);
	bool RemoveComponent (IComponent::Name const& name);
	bool RemoveComponent (IComponent* pComp);

private:
	GOSuid m_suid;

	// TODO: Abstract away the components collection into a Component Manager. (Maybe not necessary?)
	// Components are indexed in the container by their name
	typedef std::map<IComponent::Name, IComponent*> ComponentContainer;
	ComponentContainer m_components;

	// Construction is always done at the factory
	GameObject ();
	friend class GameObjectFactory;
	
	friend std::ostream& operator<< (std::ostream&, GameObject const&);
};

template <class T> T* GameObject::GetComponent () const
{
	return dynamic_cast<T*>(GetComponent(T::NAME));
}

template <class T> bool GameObject::HasComponent () const
{
	return HasComponent(T::NAME);
}


#endif