#ifndef MountComponent_hpp
#define MountComponent_hpp

#include "IComponent.hpp"
#include "GameObject.hpp"

#include <vector>
#include <ostream>

DEFINE_COMPONENT(Mount)
{
   DEFINE_COMPONENT_ESSENTIALS(Mount)   
public:

   MountComponent (std::vector<GOSuid> const& mountedObjs);
   virtual ~MountComponent ();

   std::vector<GOSuid> const& GetMountedObjs () const { return m_mountedObjs; }

private:
   std::vector<GOSuid> m_mountedObjs;

   friend std::ostream& operator<< (std::ostream& os, MountComponent const& c);
   friend std::ostream& operator<< (std::ostream& os, MountComponent const* pC);
};

#endif
