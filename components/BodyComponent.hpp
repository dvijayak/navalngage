#ifndef BodyComponent_hpp
#define BodyComponent_hpp

#include "IComponent.hpp"
#include "Geometry.hpp"
#include "Color.hpp"
#include "VectorF.hpp"

#include <ostream>

DEFINE_COMPONENT(Body)
{
	DEFINE_COMPONENT_ESSENTIALS(Body);
public:

	/// The surface vertices are expected to be in local coordinates. Note that the
	// origin is always (0,0) in local space.
	BodyComponent (PolygonF const& surface, Uint32 color=Color::Green) : m_surface(surface), m_color(color) {}
	~BodyComponent () {}

	PolygonF const& GetSurfaceLocal () const { return m_surface; }
	PolygonF& GetSurfaceLocal () { return m_surface; }
	void SetSurface (PolygonF const& surface) { m_surface = surface; }

	Uint32 GetSurfaceColor () const { return m_color; }

	/// Given:
	///   - position in world space;
	///   - rotation angle, in radians;
	/// transform the  local space surface polygon vertices to world space.
	PolygonF ComputeSurfaceWorld (VectorF const& position, float const theta=0) const;

private:
	PolygonF m_surface;
	Uint32 m_color;

	friend std::ostream& operator<< (std::ostream& os, BodyComponent const& c);
	friend std::ostream& operator<< (std::ostream& os, BodyComponent const* pC);
};

#endif