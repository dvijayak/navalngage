#include "BodyComponent.hpp"

#include "MathUtil.hpp"

#include "Color.hpp"

// It is more intuitive to design objects in local space with the
// unit circle rotated by 90 degrees, so we will "undo" this
// whenever we transform from local to world space
// CANIMPROVE: This should be configurable
static float localSpaceRotation = MathUtil::DegreesToRadians(-90);

PolygonF BodyComponent::ComputeSurfaceWorld (VectorF const& posInWorld, float const theta) const
{
	PolygonF::vertex_container_type resultVertices;

	// Transform local space to world space
	for (auto const& vertexInLocal : m_surface.vertices)
	{
		// Following must be done in order:
		// 1. Adjust convenience local space rotation
		// 2. Apply world space rotation
		// 2. Translate to world space position
		resultVertices.push_back(posInWorld + 
			(vertexInLocal.Rotate(localSpaceRotation)).Rotate(theta)
			);
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