#include "World.hpp"

World::World (float width, float height, PointF origin)
	: m_width(width)
	, m_height(height)
	, m_origin(origin)
	, m_rect(PolygonF::CreateQuad(
		PolygonF::vertex_type(origin.x - width/2.0, origin.y + height/2.0),
		PolygonF::vertex_type(origin.x + width/2.0, origin.y + height/2.0),
		PolygonF::vertex_type(origin.x + width/2.0, origin.y - height/2.0),
		PolygonF::vertex_type(origin.x - width/2.0, origin.y - height/2.0)))
{}