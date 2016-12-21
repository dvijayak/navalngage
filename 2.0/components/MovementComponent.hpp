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

	MovementComponent (VectorF const& velocity=VectorF(), float acceleration=0.0, float max=DEFAULT_MAX_ACCELERATION) : m_velocity(velocity), m_acceleration(acceleration), m_maxAcceleration(max) {}
	~MovementComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	VectorF const& GetVelocity () const { return m_velocity; }
	VectorF& GetVelocity () { return m_velocity; }
	void SetVelocity (VectorF const& velocity) { m_velocity = velocity; }

	float GetAcceleration () const { return m_acceleration; }
	void SetAcceleration (float a)
	{
		if (a > m_maxAcceleration)
		{
			a = m_maxAcceleration;
		}
		m_acceleration = a;
	}

	float GetMaxAcceleration () const { return m_maxAcceleration; }
	void SetMaxAcceleration (float const max) { m_maxAcceleration = max; }

	void Accelerate (float da) { SetAcceleration(m_acceleration + da); }

private:
	VectorF m_velocity; // speed is in m/s
	float m_acceleration; // affects only the magnitude of the velocity vector
	float m_maxAcceleration;
	// TODO: probably need a lower bound to deceleration as well
};

#endif