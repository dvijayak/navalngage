#include "WeaponComponent.hpp"

#include "Weapon.hpp"

WeaponComponent::WeaponComponent (std::unique_ptr<Weapon> pWeapon)
   : m_pWeapon(std::move(pWeapon))
{
   assert(m_pWeapon);
}

std::ostream& operator<< (std::ostream& os, WeaponComponent const& c)
{
   os << "[ WeaponComponent: ";
   os << "weapon = " << c.GetWeapon();
   os << " ]";
   return os;
}

std::ostream& operator<< (std::ostream& os, WeaponComponent const* pC)
{
   if (!pC)
   {
      os << "[ WeaponComponent: (Null) ]";
   }
   else
   {
      os << *pC;
   }
   return os;
}