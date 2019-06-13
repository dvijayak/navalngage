#ifndef SpeedComponent_hpp
#define SpeedComponent_hpp

#include "IComponent.hpp"

#include <ostream>

DEFINE_COMPONENT(Speed)
{
   DEFINE_COMPONENT_ESSENTIALS(Speed);
public:

   SpeedComponent (float speed=0.0, float maxSpeed=30.0)
      : m_speed(speed)
      , m_maxSpeed(maxSpeed)
   {}
   ~SpeedComponent () {}

   void SetSpeed (float speed);
   float GetSpeed () const { return m_speed; }
   float GetMaxSpeed () const { return m_maxSpeed; }

private:
   float m_speed; // m/s
   float m_maxSpeed;

   friend std::ostream& operator<< (std::ostream& os, SpeedComponent const& c);
   friend std::ostream& operator<< (std::ostream& os, SpeedComponent const* pC);
};

#endif