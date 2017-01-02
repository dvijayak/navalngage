#ifndef CameraZoomAction_hpp
#define CameraZoomAction_hpp

#include "CameraAction.hpp"

class CameraZoomAction : virtual public CameraAction
{
public:
	CameraZoomAction () : CameraAction(), m_zoom(0), m_zoomIsIncremental(false) {}
	virtual ~CameraZoomAction () {}

	/// Action
	void Perform ();
	std::string str () const;

	void SetZoom (float zoom) { m_zoom = zoom; }
	void SetIncremental(bool b) { m_zoomIsIncremental = b; }

private:
	float m_zoom;
	bool m_zoomIsIncremental;
};

#endif