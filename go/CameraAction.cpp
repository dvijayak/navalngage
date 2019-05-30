#include "CameraAction.hpp"

#include "CameraComponent.hpp"

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