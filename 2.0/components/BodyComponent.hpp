#ifndef BodyComponent_hpp
#define BodyComponent_hpp

#include "IComponent.hpp"
#include "Geometry.hpp"
#include "Color.hpp"
#include "VectorF.hpp"

DEFINE_COMPONENT(Body)
{
public:
	static const IComponent::Name NAME;

	/// The surface vertices are expected to be in local coordinates. Note that the
	// origin is always (0,0) in local space.
	BodyComponent (PolygonF const& surface, Uint32 color=Color::Green) : m_surface(surface), m_color(color) {}
	~BodyComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	PolygonF const& GetSurface () const { return m_surface; }
	PolygonF& GetSurface () { return m_surface; }
	void SetSurface (PolygonF const& surface) { m_surface = surface; }

	Uint32 GetSurfaceColor () const { return m_color; }

	/// Given a position in world space, transform the local space surface polygon
	/// vertices to world space.
	PolygonF ComputeSurface (VectorF const& position) const;

private:
	PolygonF m_surface;
	Uint32 m_color;
};

#endif