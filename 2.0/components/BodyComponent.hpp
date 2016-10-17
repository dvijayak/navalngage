#ifndef BodyComponent_hpp
#define BodyComponent_hpp

#include "IComponent.hpp"
#include "Geometry.hpp"
#include "Color.hpp"

class BodyComponent
	: virtual public IComponent
{
public:
	static const IComponent::Name NAME;

	BodyComponent (PolygonF const& surface, Uint32 color=Color::Green) : m_surface(surface), m_color(color) {}
	~BodyComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	PolygonF const& GetSurface () const { return m_surface; }
	PolygonF& GetSurfaceMod () { return m_surface; }
	void SetSurface (PolygonF const& surface) { m_surface = surface; }

	Uint32 GetSurfaceColor () const { return m_color; }

private:
	PolygonF m_surface;
	Uint32 m_color;
};

#endif