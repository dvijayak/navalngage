#ifndef RotationComponent_hpp
#define RotationComponent_hpp

#include "IComponent.hpp"

class RotationComponent
	: virtual public IComponent
{
public:
	static const IComponent::Name NAME;

	RotationComponent (float omega = 0.0f)
		: m_angular_speed(omega)
	{}
	~RotationComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	float GetAngularSpeed () const { return m_angular_speed; }
	void SetAngularSpeeed (float omega) { m_angular_speed = omega; }

private:
	float m_angular_speed;
};

#endif