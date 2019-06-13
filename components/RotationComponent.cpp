#include "RotationComponent.hpp"

std::ostream& operator<< (std::ostream& os, RotationComponent const& c)
{
   os << "[ RotationComponent: ";
   os << "theta = " << c.m_theta;
   os << " ]";
   return os;
}

std::ostream& operator<< (std::ostream& os, RotationComponent const* pC)
{
   if (!pC)
   {
      os << "[ RotationComponent: (Null) ]";
   }
   else
   {
      os << *pC;
   }
   return os;
}