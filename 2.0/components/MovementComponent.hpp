#ifndef MovementComponent_hpp
#define MovementComponent_hpp

#include "IComponent.hpp"
#include "VectorF.hpp"

class MovementComponent
	: virtual public IComponent
{
public:
	static const IComponent::Name NAME;

	MovementComponent (VectorF const& direction=VectorF(1,0), float speed=0.0, float maxSpeed=30.0) : m_direction(direction.NormalizeCopy()), m_speed(speed), m_maxSpeed(maxSpeed) {}
	~MovementComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	void SetDirection (VectorF const&);
	VectorF const& GetDirection () const { return m_direction; }

	void SetSpeed (float speed);
	float GetSpeed () const { return m_speed; }
	float GetMaxSpeed () const { return m_maxSpeed; }

	/// Note: direction MUST be normalized!
	VectorF GetVelocity () const { return m_direction * m_speed; }

private:
	VectorF m_direction; // ideally a unit vector

	float m_speed; // m/s
	float m_maxSpeed;

};

#endif