#include "MovementComponent.hpp"

#include "global.hpp"

const IComponent::Name MovementComponent::NAME = "MovementComponent";

void MovementComponent::SetDirection (VectorF const& direction)
{
	m_direction = direction.NormalizeCopy();
}

void MovementComponent::SetSpeed (float speed)
{
	if (speed < 0.0) // a negative speed is nonsensical as speed is after all the magnitude of the velocity vector
	{
		m_speed = 0.0;
	}
	else
	{
		// Apply max speed upper bound
		m_speed = (speed > m_maxSpeed) ? m_maxSpeed : speed;
	}
}

std::ostream& operator<< (std::ostream& os, MovementComponent const& c)
{
	os << "[ MovementComponent: ";
	os << "velocity = " << c.GetVelocity();
	os << ", direction = " << c.m_direction;
	os << ", speed = " << c.m_speed;
	os << ", maxSpeed = " << c.m_maxSpeed;
	os << " ]";
	return os;
}

std::ostream& operator<< (std::ostream& os, MovementComponent const* pC)
{
	if (!pC)
	{
		os << "[ MovementComponent: (Null) ]";
	}
	else
	{
		os << *pC;
	}
	return os;
}