#include "SpeedComponent.hpp"

const IComponent::Name SpeedComponent::NAME = "SpeedComponent";

void SpeedComponent::SetSpeed (float speed)
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

std::ostream& operator<< (std::ostream& os, SpeedComponent const& c)
{
   os << "[ SpeedComponent: ";
   os << "speed = " << c.m_speed;
   os << ", maxSpeed = " << c.m_maxSpeed;
   os << " ]";
   return os;
}

std::ostream& operator<< (std::ostream& os, SpeedComponent const* pC)
{
   if (!pC)
   {
      os << "[ SpeedComponent: (Null) ]";
   }
   else
   {
      os << *pC;
   }
   return os;
}
