#ifndef MovementComponent_hpp
#define MovementComponent_hpp

#include "IComponent.hpp"
#include "VectorF.hpp"

class MovementComponent
	: virtual public IComponent
{
public:
	static const IComponent::Name NAME;

	MovementComponent (VectorF const& velocity) : m_velocity(velocity) {}
	~MovementComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	VectorF const& GetVelocity () const { return m_velocity; }
	VectorF& GetVelocityMod () { return m_velocity; }
	void SetVelocity (VectorF const& velocity) { m_velocity = velocity; }

private:
	VectorF m_velocity;
};

#endif