#include "BodyComponent.hpp"

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