#ifndef CannonWeapon_hpp
#define CannonWeapon_hpp

#include "Weapon.hpp"

class CannonWeapon
   : virtual public Weapon
{
public:
   CannonWeapon (float range=1, float rateOfFire=1, float speed=100);
   virtual ~CannonWeapon ();

   virtual std::unique_ptr<MovableBuilder> Fire ();

   void SetSpeed (float const speed) { m_speed = speed; }
   float GetSpeed () const { return m_speed; }

private:
   float m_speed;

   friend std::ostream& operator<< (std::ostream& os, CannonWeapon const& c);
   friend std::ostream& operator<< (std::ostream& os, CannonWeapon const* pC);
};

#endif