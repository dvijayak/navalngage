#ifndef WeaponComponent_hpp
#define WeaponComponent_hpp

#include "IComponent.hpp"

#include <memory>
#include <ostream>

#include "GameObjectFactory.hpp"
#include "Weapon.hpp"

DEFINE_COMPONENT(Weapon)
{
   DEFINE_COMPONENT_ESSENTIALS(Weapon);
public:

   WeaponComponent (std::unique_ptr<Weapon> pWeapon=nullptr); // warning: makes no sense to create this component without an actual weapon - this is asserted for throughout
   virtual ~WeaponComponent () {}

   Weapon & GetWeapon () { assert(m_pWeapon); return *m_pWeapon; }
   Weapon const& GetWeapon () const { assert(m_pWeapon); return *m_pWeapon; }

private:
   std::unique_ptr<Weapon> m_pWeapon;   

   friend std::ostream& operator<< (std::ostream& os, WeaponComponent const& c);
   friend std::ostream& operator<< (std::ostream& os, WeaponComponent const* pC);
};

#endif