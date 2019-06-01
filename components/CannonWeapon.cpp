#include "CannonWeapon.hpp"

#include "MovableBuilder.hpp"

CannonWeapon::CannonWeapon (float range, float rateOfFire, float speed)
   : Weapon(range, rateOfFire)
   , m_speed(speed)
{}

CannonWeapon::~CannonWeapon ()
{}

std::unique_ptr<MovableBuilder> CannonWeapon::Fire ()
{
   std::unique_ptr<MovableBuilder> builder(new MovableBuilder());

   builder->AddSpeed(m_speed, m_speed);
   auto poly = PolygonF::CreateRect(
      -1, 0, 2, 2
   );
   for (auto & v : poly.vertices)
   {
      v.x *= 0.5, v.y *= 0.5;
   }
   builder->AddBody(poly);

   return std::move(builder);
}

std::ostream& operator<< (std::ostream& os, CannonWeapon const& c)
{
   // We stick in the delimiters
   os << "[ CannonWeapon: ";
   os << static_cast<Weapon const&>(c);
   os << " ]";
   return os;
}

std::ostream& operator<< (std::ostream& os, CannonWeapon const* pC)
{
   if (!pC)
   {
      os << "[ CannonWeapon: (Null) ]";
   }
   else
   {
      os << *pC;
   }
   return os;
}
