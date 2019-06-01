#ifndef WeaponsSystem_HPP
#define WeaponsSystem_HPP

#include "ISystem.hpp"

#include <map>
#include <list>
#include <functional>

#include "GameObject.hpp"

class GameObjectFactory;

class WeaponsSystem
   : virtual public ISystem
{
public:
   WeaponsSystem ();
   ~WeaponsSystem ();

   /// ISystem
   virtual void Update (size_t dt, GameObjectFactory & factory);

private:
   using DestroyEvaluator = std::function<bool (GameObject const&)>;
   using DestroyCandidate = std::pair<GOSuid, DestroyEvaluator>;
   std::list<DestroyCandidate> m_objectsToBeDestroyed; // need container iterators to be valid when erasing during iteration, so we use list
};

#endif