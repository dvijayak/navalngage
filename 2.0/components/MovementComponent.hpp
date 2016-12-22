#ifndef MovementComponent_hpp
#define MovementComponent_hpp

#include "IComponent.hpp"
#include "VectorF.hpp"

class MovementComponent
	: virtual public IComponent
{
public:
	static const IComponent::Name NAME;

	static constexpr float DEFAULT_MAX_ACCELERATION = 10.0;

	MovementComponent (VectorF const& velocity=VectorF(), float maxSpeed=30.0) : m_velocity(velocity), m_maxSpeed(maxSpeed) {}
	~MovementComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	VectorF const& GetVelocity () const { return m_velocity; }
	VectorF& GetVelocity () { return m_velocity; }
	void SetVelocity (VectorF const& velocity) { m_velocity = velocity; }

	float GetMaxSpeed () const { return m_maxSpeed; }

private:
	VectorF m_velocity; // speed is in m/s
	float m_maxSpeed;
};

#endif