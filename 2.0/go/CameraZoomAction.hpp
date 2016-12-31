#ifndef CameraZoomAction_hpp
#define CameraZoomAction_hpp

#include "CameraAction.hpp"

#include "CameraComponent.hpp"

class CameraZoomAction : virtual public CameraAction
{
public:
	CameraZoomAction () : CameraAction(), m_zoom(0), m_zoomIsIncremental(false) {}
	virtual ~CameraZoomAction () {}

	/// Action
	void Perform ();

	void SetZoom (float zoom) { m_zoom = zoom; }
	void SetIncremental(bool b) { m_zoomIsIncremental = b; }

private:
	float m_zoom;
	bool m_zoomIsIncremental;
};

void CameraZoomAction::Perform ()
{
	CameraAction::Perform();

	m_pSource->Get<CameraComponent>().Zoom(m_zoom, m_zoomIsIncremental);
}

#endif