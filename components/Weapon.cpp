#include "Weapon.hpp"

#include "global.hpp"
#include <cmath>

constexpr float MAX_RANGE  = 10000; // TODO: Should be configured
constexpr float MAX_RADIUS = MAX_RANGE; // TODO: Should be configured
constexpr float MAX_ROF    = 500; // i.e. a period of 2 ms, which is ridiculously quick TODO: Should be configured

Weapon::Weapon (float range, float rateOfFire)
   /* intentionally avoid initializing members as we will defer to setters */
{
   SetRange(range);
   SetImpactRadius(range); // in most cases, should be same as range
   SetRateOfFire(rateOfFire);
   SetReady(true);
}

void Weapon::SetRange (float const range)
{
   if (range < 0)
   {
      errlog("Received invalid range: {}, defaulting to zero", range);
      m_range = 0;
   }
   else
   {
      m_range = std::min(range, MAX_RANGE);
   }
}

void Weapon::SetImpactRadius (float const radius)
{
   if (radius < 0)
   {
      errlog("Received invalid impact radius: {}, defaulting to zero", radius);
      m_impactRadius = 0;
   }
   else
   {
      m_impactRadius = std::min(radius, MAX_RADIUS);
   }

}

void Weapon::SetRateOfFire (float const rof)
{
   if (rof < 0)
   {
      errlog("Received invalid rate-of-fire: {rof}, defaulting to one shot per second", rof);
      m_rateOfFire = 1;
   }
   else
   {
      m_rateOfFire = std::min(rof, MAX_ROF);
   }
}

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
