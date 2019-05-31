#ifndef FireWeaponAction_hpp
#define FireWeaponAction_hpp

#include "Action.hpp"

#include <sstream>

#include "WeaponComponent.hpp"

class FireWeaponAction : virtual public Action
{
public:
   FireWeaponAction () : Action() {}
   virtual ~FireWeaponAction () {}

   /// Action
   void Perform ();
   std::string str () const;

private:
};

void FireWeaponAction::Perform ()
{
   Action::Perform();

   assert(m_pSource);

   if (!m_pSource->Has<CWeapon>()) return;

   Weapon & weapon = m_pSource->Get<CWeapon>().GetWeapon();
   weapon.QueueToFire();
}

std::string FireWeaponAction::str () const
{
   std::stringstream ss;
   ss << Action::str() << STR_SEP << "FireWeaponAction";
   ss << Action::str_base();
   return ss.str();
}

#endif