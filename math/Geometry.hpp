#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cassert>
#include <ostream>
#include <vector>

//// Points

struct Point2F
{
	Point2F (float _x=0.0, float _y=0.0) : x(_x), y(_y) {}
	Point2F (Point2F const& other) : x(other.x), y(other.y) {}
	Point2F& operator= (Point2F const& other) { x = other.x; y = other.y; return *this; }
	~Point2F () {}

	/// Convenience
	Point2F Rotate (float const theta) const;

	float x, y;
};

typedef Point2F PointF;

std::ostream& operator<< (std::ostream& os, const Point2F& point);

struct Point3F
{
	Point3F (float _x=0.0, float _y=0.0, float _z=0.0) : x(_x), y(_y), z(_z) {}
	Point3F (const Point3F& other) : x(other.x), y(other.y), z(other.z) {}
	Point3F& operator= (const Point3F& other) { x = other.x; y = other.y; z = other.z; return *this; }
	~Point3F () {}

	float x, y, z;
};

std::ostream& operator<< (std::ostream& os, const Point3F& point);


//// Lines

// CANIMPROVE: I don't like the duplication here between 2F and 3F

template <class Point>
struct LineSegment
{
	typedef Point point_type;

	LineSegment (const Point& _start=Point(), const Point& _end=Point() ) : start(_start), end(_end) {}
	LineSegment (const LineSegment& other) : start(other.start), end(other.end) {}
	LineSegment& operator= (const LineSegment& other) { start = other.start; end = other.end; return *this; }
	~LineSegment () {}

	Point start, end;
};

// Useful typedefs
typedef LineSegment<Point2F> LineSegment2F;
typedef LineSegment<Point3F> LineSegment3F;
typedef LineSegment2F LineSegmentF;

template <class Point>
std::ostream& operator<< (std::ostream& os, LineSegment<Point> const& line)
{
	os << "(" << line.start << ", " << line.end << ")";
	return os;
}

//// Polygons

template <class Vertex>
struct Polygon
{
	typedef Polygon<Vertex> polygon_type;
	typedef Vertex vertex_type;
	typedef std::vector<Vertex> vertex_container_type;

	size_t n; // Number of vertices
	vertex_container_type vertices;

	/// Note: we should get the rule of five for free, including move semantics

	void ComputeEdges (std::vector< LineSegment<Vertex> >& result) const;

	/// Obtain the vertex at the given index
	Vertex& operator[] (const size_t i)	{ assert(i <= n); return vertices[i]; }

	// Caller is always responsible for freeing memory for the following create methods

	static Polygon CreateNPolygon (Vertex vertices[], size_t _n = 4);
	static Polygon CreateNPolygon (vertex_container_type const& _vertices); // CANIMPROVE: use std::back_inserter (although I feel that this might be overkill)

	static Polygon CreateTriangle (Vertex v[3]) { return CreateTriangle(v[0], v[1], v[2]); }
	static Polygon CreateTriangle (Vertex v1, Vertex v2, Vertex v3);

	static Polygon CreateQuad (Vertex v[4]) { return CreateQuad(v[0], v[1], v[2], v[3]); }
	static Polygon CreateQuad (Vertex v1, Vertex v2, Vertex v3, Vertex v4);

	static Polygon CreateRect (Vertex const& o, float width, float height);
	static Polygon CreateRect (float x, float y, float width, float height) { return CreateRect(Vertex(x, y), width, height); }
};

// Useful typedefs
typedef Polygon<Point2F> Polygon2F;
typedef Polygon<Point3F> Polygon3F;
typedef Polygon2F PolygonF;

template <class Vertex>
void Polygon<Vertex>::ComputeEdges (std::vector< LineSegment<Vertex> >& result) const
{
	// Note: `n` and `vertices` are struct members
	assert(n >= 3 && !vertices.empty());

	result.clear();
	for (size_t i = 0; i < n; ++i)
	{
		Vertex s = vertices[i];
		Vertex e = vertices[(i + 1) % n]; // last edge's end-point is the first vertex
		result.push_back(LineSegment<Vertex>(s, e));
	}
}

template <class Vertex>
Polygon<Vertex> Polygon<Vertex>::CreateNPolygon (Vertex vertices[], size_t n)
{
	// Create a polygon with at least 3 vertices
	assert(n >= 3);

	polygon_type p;
	p.n = n;

	// Set vertices
	p.vertices = vertex_container_type(n);
	for (size_t i = 0; i < n; ++i)
	{
		p.vertices[i] = vertices[i];
	}

	return p;
}

template <class Vertex>
Polygon<Vertex> Polygon<Vertex>::CreateNPolygon (vertex_container_type const& vertices)
{
	// Create a polygon with at least 3 vertices
	size_t n = vertices.size();
	assert(!vertices.empty() && n >= 3);

	polygon_type p;
	p.n = n;

	// Set vertices
	p.vertices = vertices;

	return p;
}

template <class Vertex>
Polygon<Vertex> Polygon<Vertex>::CreateTriangle (Vertex v1, Vertex v2, Vertex v3)
{
	polygon_type p;
	p.n = 3;

	// Set vertices
	p.vertices = vertex_container_type(3);
	p.vertices[0] = v1;
	p.vertices[1] = v2;
	p.vertices[2] = v3;

	return p;
}

template <class Vertex>
Polygon<Vertex> Polygon<Vertex>::CreateQuad (Vertex v1, Vertex v2, Vertex v3, Vertex v4)
{
	polygon_type p;
	p.n = 4;

	// Set vertices
	p.vertices = vertex_container_type(4);
	p.vertices[0] = v1;
	p.vertices[1] = v2;
	p.vertices[2] = v3;
	p.vertices[3] = v4;

	return p;
}

template <class Vertex>
Polygon<Vertex> Polygon<Vertex>::CreateRect (Vertex const& o, float width, float height)
{
	polygon_type p;
	p.n = 4;

	//
	// Given the standard x-y axes (+x rightwards, +y upwards):
	//
	//    0                             1
	// (o.x, o.y)                     (o.x + width, o.y)
	//    *-----------------------------*
	//    |                             |
	//    |                             |
	//    |                             |
	//    *-----------------------------*
	// (o.x, o.y - height)            (o.x + width, o.y - height)
	//    3                             2
	//

	// Set vertices
	p.vertices = vertex_container_type(4);
	p.vertices[0] = o;
	p.vertices[1] = Vertex(o.x + width, o.y);
	p.vertices[2] = Vertex(o.x + width, o.y - height);
	p.vertices[3] = Vertex(o.x, o.y - height);

	return p;
}

template <class Vertex>
std::ostream& operator<< (std::ostream& os, Polygon<Vertex> const& polygon)
{
	os << "( ";
	for (size_t i = 0; i < polygon.n; ++i)
	{
		os << polygon.vertices[i];
		if (i != polygon.n - 1)
		{
			os << ", ";
		}
	}
	os << " )";
	return os;
}

class Vector2F;
struct Rectangle2F
{
	float x, y;
	float width, height;

	Rectangle2F (float _x=0, float _y=0, float w=0, float h=0) : x(_x), y(_y), width(w), height(h) {}
	Rectangle2F (Point2F const& p, float w, float h) : x(p.x), y(p.y), width(w), height(h) {}
	Rectangle2F (Vector2F const& v, float w, float h);
	// Rectangle2F (Rectangle2F const& other) : x(other.x), y(other.y), width(other.width), height(other.height) {}
	// Rectangle2F& operator= (Rectangle2F const& other);
};
typedef Rectangle2F RectangleF;

std::ostream& operator<< (std::ostream& os, Rectangle2F const& rect);

// inline Rectangle2F& Rectangle2F::operator= (Rectangle2F const& other)
// {
// 	x = other.x;
// 	y = other.y;
// 	width = other.width;
// 	height = other.height;
// 	return *this;
// }

// LineSegment2F CalculateIntersection (Rectangle2F const&, )

////

enum ClippingTestResult
{
	TRIVIAL_ACCEPT,
	TRIVIAL_REJECT,
	NON_TRIVIAL,
	ERROR
};

#endif
