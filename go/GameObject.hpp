#ifndef GO_HPP
#define GO_HPP

#include <memory>
#include <map>
#include <cassert>

#include "IComponent.hpp"

typedef size_t GOSuid;

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

	/// Convenience - exactly the same as HasComponent<T>
	template <class T> bool Has () const;
	/// Convenience - similar to GetComponent<T> except that it
	/// returns a reference instead of a pointer. Callers are
	/// expected to rely on Has<T> to check for existence.
	template <class T> T& Get () const;

private:
	GOSuid m_suid;

	// TODO: Abstract away the components collection into a Component Manager. (Maybe not necessary?)
	// Components are indexed in the container by their name
	typedef std::map<IComponent::Name, std::unique_ptr<IComponent>> ComponentContainer;
	ComponentContainer m_components;

	/// Construction is always done at the factory
	GameObject ();
	friend class GameObjectFactory;
	
	friend std::ostream& operator<< (std::ostream&, GameObject const&);
	friend std::ostream& operator<< (std::ostream&, GameObject const*);
};

template <class T>
inline T* GameObject::GetComponent () const
{
	return dynamic_cast<T*>(GetComponent(T::NAME));
}

template <class T>
inline bool GameObject::HasComponent () const
{
	return HasComponent(T::NAME);
}

/// Conveniences

template <class T>
inline bool GameObject::Has () const
{
	return HasComponent<T>();
}

template <class T>
inline T& GameObject::Get () const
{
	T* p = GetComponent<T>();
	assert(p);
	return *p;
}

#endif