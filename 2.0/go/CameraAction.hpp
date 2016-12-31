#ifndef CameraAction_hpp
#define CameraAction_hpp

#include "Action.hpp"

#include "CameraComponent.hpp"

class CameraAction : virtual public Action
{
public:
	CameraAction () : Action() {}
	virtual ~CameraAction () {}

	/// Action
	virtual void Perform () = 0;
	void SetSource (GameObject* pGo);

	inline void SetCamera (GameObject* pGo) { SetSource(pGo); } // convenience function
};

void CameraAction::Perform ()
{
	Action::Perform();

	assert(m_pSource);
}

void CameraAction::SetSource (GameObject* pGo)
{
	assert(pGo && pGo->HasComponent<CameraComponent>());
	Action::SetSource(pGo);
}

#endif