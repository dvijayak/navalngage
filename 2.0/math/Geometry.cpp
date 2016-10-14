#include "Geometry.hpp"

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