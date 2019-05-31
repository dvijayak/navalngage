#include "RotationSpeedComponent.hpp"

const IComponent::Name RotationSpeedComponent::NAME = "RotationSpeedComponent";

void RotationSpeedComponent::SetAngularSpeed (float omega)
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