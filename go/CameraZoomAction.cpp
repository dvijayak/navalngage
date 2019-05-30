#include "CameraZoomAction.hpp"

#include <sstream>
#include "CameraComponent.hpp"

void CameraZoomAction::Perform ()
{
	CameraAction::Perform();

	m_pSource->Get<CameraComponent>().Zoom(m_zoom, m_zoomIsIncremental);
}

std::string CameraZoomAction::str () const
{
	std::stringstream ss;
	ss << Action::str() << STR_SEP << "CameraZoomAction";
	ss << Action::str_base();
	ss << STR_SEP << "zoom=" << m_zoom;
	ss << STR_SEP << "isIncremental=" << m_zoomIsIncremental;
	return ss.str();
}