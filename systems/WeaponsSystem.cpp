#include "WeaponsSystem.hpp"

#include "VectorF.hpp"

#include "TimerManager.hpp"

#include "GameObjectFactory.hpp"
#include "MovableBuilder.hpp"

#include "PositionComponent.hpp"
#include "SpeedComponent.hpp"
#include "RotationComponent.hpp"
#include "WeaponComponent.hpp"

#include "global.hpp" // for logging

WeaponsSystem::WeaponsSystem ()
{}

WeaponsSystem::~WeaponsSystem ()
{}

void WeaponsSystem::Update (size_t dt, GameObjectFactory & factory)
{
   // First, destroy projectiles that need to be deleted
   // CANIMPROVE: Could be made generic to all systems?
   for (auto candidate = m_objectsToBeDestroyed.begin(); candidate != m_objectsToBeDestroyed.end();)
   {
      auto suid = candidate->first;
      auto pGo = factory.Resolve(suid);
      if (pGo && (candidate->second)(*pGo))
      {
         factory.Destroy(suid);         

         // Remove the element and update the iterator to the next one
         // Note: must use a container where iterators for the rest of the container
         // are not invalidated after a successful erase call
         candidate = m_objectsToBeDestroyed.erase(candidate);
      }
      else
      {
         // Nothing to be done, so just move to the next candidate
         ++candidate;
      }
   }

   const auto filter = [] (GameObject const& go) { return
      go.Has<PositionComponent>() &&
      go.Has<RotationComponent>() &&
      go.Has<WeaponComponent>() &&
      go.Get<WeaponComponent>().GetWeapon().IsQueuedToFire();
   };
   for (auto & pGo : factory.ResolveObjects(filter))
   {
      auto & weapon = pGo->Get<WeaponComponent>().GetWeapon();

      if (!weapon.IsReady())
      {
         weapon.ClearFire();
         continue;
      }

      auto const& pos = pGo->Get<PositionComponent>().GetPosition();
      auto dir = pGo->Get<RotationComponent>().GetDirection();

      // Fire away!
      auto builder = weapon.Fire();
      builder->AddPosition(pos);
      builder->AddRotation(pGo->Get<RotationComponent>().GetRotationAngle());
      auto & projectile = factory.Create(*builder);
      weapon.ClearFire();

      // Queue cooldown refresh
      weapon.SetReady(false); // disable weapon during cooldown
      float cooldown = weapon.GetCooldownPeriod();
      auto weaponSuid = pGo->GetSuid();
      TimerManager::Instance().StartTimer(cooldown, [=, &factory](void) {
         auto pWeapon = factory.Resolve(weaponSuid);
         if (pWeapon && pWeapon->Has<WeaponComponent>()) // protect against deletion
         {
            pWeapon->Get<WeaponComponent>().GetWeapon().SetReady(true);
         }
      });

      // Queue projectile for deletion when it has consumed its range
      float range = weapon.GetRange();
      DestroyEvaluator destroyEvaluator = [=](GameObject const& go) {
         // TODO: this will ONLY work with linear projectiles that do NOT change direction at all along the projectile path
         // TODO: To work with non-linear paths, do a circle inclusion test instead,
         // where the circle is centered on the launch point (pos) and has radius range.
         VectorF newDir = go.Get<RotationComponent>().GetDirection();
         assert(dir.GetX() == newDir.GetX() && dir.GetY() == newDir.GetY());
         auto displacement = go.Get<PositionComponent>().GetPosition() - pos;
         return displacement.Norm() >= range;
      };
      m_objectsToBeDestroyed.push_back(std::make_pair(projectile.GetSuid(), destroyEvaluator));
   }
}