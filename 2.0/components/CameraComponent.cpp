#include "CameraComponent.hpp"

#include <cmath>

#include "VectorF.hpp"
#include "World.hpp"

static constexpr float MIN_VIEWSCALE = 10;
static constexpr float MAX_VIEWSCALE = 60;
static constexpr float MIN_SPEED = 1; // m/s
static constexpr float MAX_SPEED = 10; // m/s

const IComponent::Name CameraComponent::NAME = "CameraComponent";

CameraComponent::CameraComponent (World* pWorld, float x, float y, float scale)
	: m_pWorld(pWorld)
	, m_viewRectangle(x, y, 0, 0)
	, m_minViewScale(MIN_VIEWSCALE)
	, m_maxViewScale(MAX_VIEWSCALE)
	, m_viewScale(scale)
	, m_minMoveSpeed(MIN_SPEED)
	, m_maxMoveSpeed(MAX_SPEED)
	, m_pFollowTarget(0)
{
	SetViewScale(scale); // validate the provided scale before creating the view rect
}

CameraComponent::CameraComponent (World* pWorld, RectangleF const& rect)
	: m_pWorld(pWorld)
	, m_viewRectangle(rect)
	, m_minViewScale(MIN_VIEWSCALE)
	, m_maxViewScale(MAX_VIEWSCALE)
	, m_viewScale(m_minViewScale)
	, m_minMoveSpeed(MIN_SPEED)
	, m_maxMoveSpeed(MAX_SPEED)
	, m_pFollowTarget(0)
{
	UpdateView();
}

void CameraComponent::SetViewScale (float val)
{
	// Ensure that the new scale value is valid
	m_viewScale = std::abs(val); // a negative dimension makes no sense
	m_viewScale = std::max(m_viewScale, m_minViewScale);
	m_viewScale = std::min(m_viewScale, m_maxViewScale);

	UpdateView();
}

void CameraComponent::UpdateView ()
{
	// Update camera to fit sensibly within the world
	m_viewRectangle.width = m_pWorld->GetWidth()/m_viewScale;
	m_viewRectangle.height = m_pWorld->GetHeight()/m_viewScale;
}

void CameraComponent::Attach (World* pWorld)
{
	if (!pWorld) return;

	m_pWorld = pWorld;

	UpdateView();
}

void CameraComponent::Zoom (float val, bool bIsIncrement)
{
	if (bIsIncrement)
	{
		val += m_viewScale;
	}

	SetViewScale(val);
}

void CameraComponent::Pan (Vector2F& cameraPosition, float dx, float dy)
{
	cameraPosition += Vector2F(dx, dy);
}

void CameraComponent::WorldToScreen (Point2F& p) const
{
	// 1. translate to camera position (is this what we're actually doing though???)
	p.x -= m_viewRectangle.x;
	p.y -= m_viewRectangle.y;

	// 2. reflect over the x-axis 
	// (Since screen space origin is 0,0 on top-left corner with +x rightwards 
	// and +y downwards)
	p.y = -p.y;

	// 3. normalized device coordinates (we choose the range as [0,1])
	p.x /= m_viewRectangle.width;
	p.y /= m_viewRectangle.height;
}

void CameraComponent::ScreenToWorld (Point2F& p) const
{
	// This should be the reverse (inverse?) of WorldToScreen

	// // 1. 
	// p.x *= m_viewRectangle.width;
	// p.y *= m_viewRectangle.height;
	// console("{}",p);

	// 2. reflect over the x-axis 
	// (Since screen space origin is 0,0 on top-left corner with +x rightwards 
	// and +y downwards)
	p.y = -p.y;
	// console("{}",p);

	// 3. translate to camera position (is this what we're actually doing though???)
	p.x += m_viewRectangle.x;
	p.y += m_viewRectangle.y;
	// console("{}",p);
}

bool CameraComponent::Includes (Point2F const& p) const
{
	//
	// A point is considered to be included by a rectangle if its coordinates lie
	// within the bounds of the rectangle. In other words, given a point P and a
	// rectangle R, P is included by R if R.x <= P.x <= R.x+width and
	// R.y-height <= P.y <= R.y.
	//
	// Given the standard x-y axes (+x rightwards, +y upwards):
	//
	//    0             *U              1
	// (o.x, o.y)                     (o.x + width, o.y)
	//    *-----------------------------*
	// *S |                             |
	//    |      *P                     *R
	//    |                             |   *T
	//    *----------------------*Q-----*
	// (o.x, o.y - height)            (o.x + width, o.y - height)
	//    3                             2
	//            *V
	//
	// In the above diagram, points P, Q and R are included but points S, T, U and V
	// are not included.
	//
	return (p.x >= m_viewRectangle.x && p.x <= m_viewRectangle.x+m_viewRectangle.width) 
		 && (p.y <= m_viewRectangle.y && p.y >= m_viewRectangle.y-m_viewRectangle.height);
}

std::ostream& operator<< (std::ostream& os, CameraComponent const& c)
{
	os << "[ CameraComponent: ";
	os << c.m_viewRectangle;
	os << " ]";
	return os;
}

std::ostream& operator<< (std::ostream& os, CameraComponent const* pC)
{
	if (!pC)
	{
		os << "[ CameraComponent: (Null) ]";
	}
	else
	{
		os << *pC;
	}
	return os;
}