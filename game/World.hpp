#ifndef World_HPP
#define World_HPP

#include "Geometry.hpp"

class World
{
public:
	World (float width = 1000, float height = 800, PointF origin = PointF(0, 0));

	float GetWidth () const { return m_width; }
	float GetHeight () const { return m_height; }

	PointF GetOrigin () const { return m_origin; }

	PolygonF const& GetRect () const { return m_rect; }
	PolygonF& GetRectMod () { return m_rect; }
	void SetRect (PolygonF const& poly) { m_rect = poly; }

private:
	float m_width;
	float m_height;

	PointF m_origin;

	PolygonF m_rect;
};

#endif