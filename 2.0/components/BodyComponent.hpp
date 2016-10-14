#ifndef BodyComponent_hpp
#define BodyComponent_hpp

#include "IComponent.hpp"
#include "Geometry.hpp"

class BodyComponent
	: virtual public IComponent
{
public:
	static const IComponent::Name NAME;

	BodyComponent (PolygonF const& surface) : m_surface(surface) {}
	~BodyComponent () {} // TODO: Keep in mind the delete responsibility of surface polygon. Maybe it makes more sense to store a pointer instead of the object itself so that we can use RAII?

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	PolygonF const& GetSurface () const { return m_surface; }
	PolygonF& GetSurfaceMod () { return m_surface; }
	void SetSurface (PolygonF const& surface) { m_surface = surface; }

private:
	PolygonF m_surface;
};
const IComponent::Name BodyComponent::NAME = "BodyComponent";

#endif