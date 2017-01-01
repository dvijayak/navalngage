#include "BodyComponent.hpp"

#include "Color.hpp"

const IComponent::Name BodyComponent::NAME = "BodyComponent";

PolygonF BodyComponent::ComputeSurface (VectorF const& position) const
{
	PolygonF::vertex_container_type resultVertices;

	// Transform local space to world space
	// We currently only need to translate each vertex by the given position vector
	for (auto const& v : m_surface.vertices)
	{
		resultVertices.push_back(position + v);
	}

	return PolygonF::CreateNPolygon(resultVertices);
}

std::ostream& operator<< (std::ostream& os, BodyComponent const& c)
{
	os << "[ BodyComponent: ";
	os << "surface = " << c.m_surface;
	os << ", color = " << Color::str(c.m_color);
	os << " ]";
	return os;
}

std::ostream& operator<< (std::ostream& os, BodyComponent const* pC)
{
	if (!pC)
	{
		os << "[ BodyComponent: (Null) ]";
	}
	else
	{
		os << *pC;
	}
	return os;
}