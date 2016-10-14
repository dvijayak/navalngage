#ifndef MovementComponent_hpp
#define MovementComponent_hpp

#include "IComponent.hpp"
#include "Vector2F.hpp"

class MovementComponent
	: virtual public IComponent
{
public:
	static const IComponent::Name NAME;

	MovementComponent (Vector2F const& velocity) : m_velocity(velocity) {}
	~MovementComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	Vector2F const& GetVelocity () const { return m_velocity; }
	Vector2F& GetVelocityMod () { return m_velocity; }
	void SetVelocity (Vector2F const& velocity) { m_velocity = velocity; }

private:
	Vector2F m_velocity;
};
const IComponent::Name MovementComponent::NAME = "MovementComponent";

#endif