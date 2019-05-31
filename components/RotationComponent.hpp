#ifndef RotationComponent_hpp
#define RotationComponent_hpp

#include "IComponent.hpp"

#include <ostream>

DEFINE_COMPONENT(Rotation)
{
public:
   static const IComponent::Name NAME;

   RotationComponent (float const theta)
      : m_theta(theta)
   {}
   ~RotationComponent () {}

   /// IComponent
   IComponent::Name GetName () const { return NAME; }

   void SetRotationAngle (float const theta) { m_theta = theta; }
   float GetRotationAngle () const { return m_theta; }

private:
   float m_theta; // in radians

   friend std::ostream& operator<< (std::ostream& os, RotationComponent const& c);
   friend std::ostream& operator<< (std::ostream& os, RotationComponent const* pC);
};

#endif