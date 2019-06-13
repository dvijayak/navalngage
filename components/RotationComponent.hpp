#ifndef RotationComponent_hpp
#define RotationComponent_hpp

#include "IComponent.hpp"

#include <ostream>

#include "VectorF.hpp"

DEFINE_COMPONENT(Rotation)
{
   DEFINE_COMPONENT_ESSENTIALS(Rotation);
public:

   RotationComponent (float const theta)
      : m_theta(theta)
   {}
   ~RotationComponent () {}

   void SetRotationAngle (float const theta) { m_theta = theta; }
   float GetRotationAngle () const { return m_theta; }

   VectorF GetDirection () const { return VectorF(1, 0).Rotate(m_theta); }

private:
   float m_theta; // in radians

   friend std::ostream& operator<< (std::ostream& os, RotationComponent const& c);
   friend std::ostream& operator<< (std::ostream& os, RotationComponent const* pC);
};

#endif