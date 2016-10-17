#include "Geometry.hpp"

#include "VectorF.hpp"

std::ostream& operator<< (std::ostream& os, const Point2F& point)
{
	os << "(" << point.x << ", " << point.y << ")";
	return os;
}

std::ostream& operator<< (std::ostream& os, const Point3F& point)
{
	os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
	return os;
}

Rectangle2F::Rectangle2F (Vector2F const& v, float w, float h)
	: x(v.GetX())
	, y(v.GetY())
	, width(w)
	, height(h)
{}

std::ostream& operator<< (std::ostream& os, Rectangle2F const& rect)
{
	os << "( ";
	os << Point2F(rect.x, rect.y) << ", ";
	os << Point2F(rect.x + rect.width, rect.y) << ", ";
	os << Point2F(rect.x + rect.width, rect.y - rect.height) << ", ";
	os << Point2F(rect.x, rect.y - rect.height);
	os << " )";
	return os;
}