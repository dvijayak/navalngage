#include "Weapon.hpp"

Weapon::Weapon (float range, float rateOfFire)
   : m_range(range)
   , m_impactRadius(range) // in most cases, should be same as range
   , m_rateOfFire(rateOfFire)
   , m_isReady(true)
{}

std::ostream& operator<< (std::ostream& os, Weapon const& c)
{
   // Expecting derived classes to stick in the delimiters
   os << "range = " << c.m_range;
   os << ", impactRadius = " << c.m_impactRadius;
   os << ", rateOfFire = " << c.m_rateOfFire;
   os << ", isReady = " << (c.m_isReady ? "yes" : "no");
   return os;
}

std::ostream& operator<< (std::ostream& os, Weapon const* pC)
{
   if (!pC)
   {
      os << "[ Weapon: (Null) ]";
   }
   else
   {
      os << *pC;
   }
   return os;
}
