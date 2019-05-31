#include "WeaponsSystem.hpp"

#include "VectorF.hpp"

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
   while (!m_objectsToBeDestroyed.empty())
   {
      auto & candidate = m_objectsToBeDestroyed.front();
      m_objectsToBeDestroyed.pop();
      
      auto suid = candidate.first;
      auto pGo = factory.Resolve(suid);
      if (pGo && (candidate.second)(*pGo))
      {
         factory.Destroy(suid);
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
      auto const& pos = pGo->Get<PositionComponent>().GetPosition();
      VectorF dir = pGo->Get<RotationComponent>().GetDirection();
      auto & weapon = pGo->Get<WeaponComponent>().GetWeapon();

      // Fire away!
      auto builder = weapon.Fire();
      builder->AddPosition(pos);
      builder->AddRotation(pGo->Get<RotationComponent>().GetRotationAngle());
      auto & go = factory.Create(*builder);
      weapon.ClearFire();

      // Queue projectile for deletion when it has consumed its range
      float range = weapon.GetRange();
      DestroyEvaluator destroyEvaluator = [pos, dir, range](GameObject const& go) {
         // TODO: this will ONLY work with linear projectiles that do NOT change direction at all along the projectile path
         VectorF newDir = go.Get<RotationComponent>().GetDirection();
         assert(dir.GetX() == newDir.GetX() && dir.GetY() == newDir.GetY());
         auto displacement = go.Get<PositionComponent>().GetPosition() - pos;
         return displacement.Norm() >= range;
      };
      m_objectsToBeDestroyed.push(std::make_pair(go.GetSuid(), destroyEvaluator));
   }
}