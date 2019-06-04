#ifndef Weapon_hpp
#define Weapon_hpp

#include <memory>
#include <ostream>

class MovableBuilder;

/// Abstract base class which holds general weapon info + behaviour
class Weapon
{
public:
   Weapon (float range=1, float rateOfFire=1);
   virtual ~Weapon () {}

   /// Is the weapon deemed ready/available to be fired?
   virtual bool IsReady () { return m_isReady; }
   virtual void SetReady (bool const val) { m_isReady = val; }


   /// The magic happens here!
   /// Derived classes are responsible for implementing this according to their custom
   /// weapon behaviour. The result must be a template that a projectile GameObject can
   /// then be constructed from.
   virtual std::unique_ptr<MovableBuilder> Fire () = 0;

   void QueueToFire () { m_isQueuedToFire = true; }
   void ClearFire () { m_isQueuedToFire = false; } // TODO: More consistent method name
   bool IsQueuedToFire () const { return m_isQueuedToFire; }

   void SetRange (float const range);
   float GetRange () const { return m_range; }

   void SetImpactRadius (float const radius);
   float GetImpactRadius () const { return m_impactRadius; }

   void SetRateOfFire (float const rof);
   float GetRateOfFire () const { return m_rateOfFire; }
   float GetCooldownPeriod () const { return 1000.0/m_rateOfFire; }

private:
   float m_range; // m
   float m_impactRadius; // m
   float m_rateOfFire; // shots/s

   bool m_isReady;
   bool m_isQueuedToFire;

   friend std::ostream& operator<< (std::ostream& os, Weapon const& c);
   friend std::ostream& operator<< (std::ostream& os, Weapon const* pC);
};

#endif