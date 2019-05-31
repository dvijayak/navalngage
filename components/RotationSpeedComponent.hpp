#ifndef RotationSpeedComponent_hpp
#define RotationSpeedComponent_hpp

#include "IComponent.hpp"

/// TODO

DEFINE_COMPONENT(RotationSpeed)
{
public:
	static const IComponent::Name NAME;

	RotationSpeedComponent (float omega = 0.0, float max = 15.0)
		: m_angularSpeed(omega)
		, m_maxAngularSpeed(max)
	{}
	~RotationSpeedComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	void SetAngularSpeed (float);
	float GetAngularSpeed () const { return m_angularSpeed; }

	float GetMaxAngularSpeed () const { return m_maxAngularSpeed; }

private:
	float m_angularSpeed; // rads/s, +ve = clockwise; -ve = counter-clockwise; 0 = no change in rotation
	float m_maxAngularSpeed;
};

#endif