#include "MountComponent.hpp"

#include "Util.hpp"

MountComponent::MountComponent (std::vector<GOSuid> const& objs)
   : m_mountedObjs(objs)
{}

MountComponent::~MountComponent ()
{}

std::ostream& operator<< (std::ostream& os, MountComponent const& c)
{
   os << "[ MountComponent: ";
   os << "mountedObjs = " << c.m_mountedObjs;
   os << " ]";
   return os;
}

std::ostream& operator<< (std::ostream& os, MountComponent const* pC)
{
   if (!pC)
   {
      os << "[ MountComponent: (Null) ]";
   }
   else
   {
      os << *pC;
   }
   return os;
}
