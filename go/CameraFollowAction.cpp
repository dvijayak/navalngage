#include "CameraFollowAction.hpp"

#include <sstream>

#include "CameraComponent.hpp"
#include "PositionComponent.hpp"

void CameraFollowAction::Perform ()
{
	CameraAction::Perform();

	if (!m_pTarget)
	{
		m_pSource->Get<CameraComponent>().UnFollow();
	}
	else
	{
		m_pSource->Get<CameraComponent>().Follow(m_pTarget);
	}
}

void CameraFollowAction::SetTarget (GameObject* pGo)
{
	if (pGo)
	{
		assert(pGo->Has<PositionComponent>());
	}

	m_pTarget = pGo;
}

std::string CameraFollowAction::str () const
{
	std::stringstream ss;
	ss << Action::str() << STR_SEP << "CameraFollowAction";
	ss << Action::str_base();
	return ss.str();
}