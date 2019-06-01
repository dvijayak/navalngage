#ifndef CameraComponent_HPP
#define CameraComponent_HPP

#include "IComponent.hpp"
#include "Geometry.hpp"

#include <memory>
#include <ostream>

class World;
class GameObject;
class CameraSystem;
class Vector2F;
class ILineClipper;

DEFINE_COMPONENT(Camera)
{
public:
	static const IComponent::Name NAME;

	CameraComponent (World* pWorld=0, float x=0, float y=0, float scale=50);
	CameraComponent (World* pWorld, RectangleF const& rect);
	virtual ~CameraComponent ();

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	/// Should be used mostly by initializing code
	void SetViewScale (float val);

	void Attach (World* pWorld);
	void Detach () { m_pWorld = 0; }
	World* GetWorld () const { return m_pWorld; }

	void Follow (GameObject *pGo) { if (pGo) m_pFollowTarget = pGo; }
	void UnFollow () { m_pFollowTarget = 0; }
	GameObject* GetFollowTarget () const { return m_pFollowTarget; }

	/// By default, the given zoom value is an increment/decrement delta to adjust
	/// the current zoom by. If you wish to set the zoom to the given value, then
	/// pass in `bIsIncrement` as false. In either case, the resultant zoom value
	/// cannot be less than m_minViewScale or greater than m_maxViewScale.
	void Zoom (float val, bool bIsIncrement=true);

	/// Note that either of dx and dy can be zero if you wish to pan on only one axis
	void Pan (Vector2F& cameraPosition, float dx, float dy);

	void WorldToScreen (Point2F&) const;
	void ScreenToWorld (Point2F&) const;

	bool Includes (Point2F const&) const;

	ClippingTestResult ClipToViewport (LineSegment2F & line) const;

private:
	void UpdateView ();

	World* m_pWorld;
	RectangleF m_viewRectangle;

	// Zoom level controls
	float m_minViewScale;
	float m_maxViewScale;
	float m_viewScale;

	// Pan controls
	float m_minMoveSpeed;
	float m_maxMoveSpeed;

	GameObject * m_pFollowTarget = 0;

	std::unique_ptr<ILineClipper> m_pClipper;

	friend CameraSystem;

	friend std::ostream& operator<< (std::ostream& os, CameraComponent const& c);
	friend std::ostream& operator<< (std::ostream& os, CameraComponent const* pC);
};

#endif