#ifndef CameraFollowAction_hpp
#define CameraFollowAction_hpp

#include "CameraAction.hpp"

#include "CameraComponent.hpp"
#include "PositionComponent.hpp"

class CameraFollowAction : virtual public CameraAction
{
public:
	CameraFollowAction () : CameraAction() {}
	virtual ~CameraFollowAction () {}

	/// Action
	void Perform ();
	void SetTarget (GameObject* pGo);
};

void CameraFollowAction::Perform ()
{
	CameraAction::Perform();

	if (!m_pTarget)
	{
		m_pSource->GetComponent<CameraComponent>()->UnFollow();
	}
	else
	{
		m_pSource->GetComponent<CameraComponent>()->Follow(m_pTarget);
	}
}

void CameraFollowAction::SetTarget (GameObject* pGo)
{
	if (pGo)
	{
		assert(pGo->HasComponent<PositionComponent>());
	}

	m_pTarget = pGo;
}

#endif