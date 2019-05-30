#ifndef RotationComponent_hpp
#define RotationComponent_hpp

#include "IComponent.hpp"

/// DEPRECATED

class RotationComponent
	: virtual public IComponent
{
public:
	static const IComponent::Name NAME;

	RotationComponent (float omega = 0.0, float max = 15.0)
		: m_angularSpeed(omega)
		, m_maxAngularSpeed(max)
	{}
	~RotationComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	void SetAngularSpeed (float);
	float GetAngularSpeed () const { return m_angularSpeed; }

	float GetMaxAngularSpeed () const { return m_maxAngularSpeed; }

private:
	float m_angularSpeed; // rads/s, +ve = clockwise; -ve = counter-clockwise; 0 = no rotation
	float m_maxAngularSpeed;
};

#endif