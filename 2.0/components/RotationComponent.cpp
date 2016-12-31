#include "RotationComponent.hpp"

const IComponent::Name RotationComponent::NAME = "RotationComponent";

void RotationComponent::SetAngularSpeed (float omega)
{
	float minAngularSpeed = -m_maxAngularSpeed;
	if (omega < minAngularSpeed)
	{
		m_angularSpeed = minAngularSpeed;
	}
	else
	{
		// Apply max speed upper bound
		m_angularSpeed = (omega > m_maxAngularSpeed) ? m_maxAngularSpeed : omega;
	}
}