#ifndef RelativePositionComponent_HPP
#define RelativePositionComponent_HPP

#include "IComponent.hpp"
#include "VectorF.hpp"

#include <ostream>

/// Position is relative to another object's position. That is, it exists in a 
/// coordinate space where the associated position is the origin (0,0).
DEFINE_COMPONENT(RelativePosition)
{
	DEFINE_COMPONENT_ESSENTIALS(RelativePosition);
public:

	RelativePositionComponent (float x = 0.0f, float y = 0.0f) : m_relativePosition(x, y) {}
	RelativePositionComponent (VectorF const& pos) : m_relativePosition(pos) {}
	~RelativePositionComponent () {}

	VectorF const& GetRelativePosition () const { return m_relativePosition; }
	VectorF& GetRelativePosition () { return m_relativePosition; }
	void SetRelativePosition (VectorF const& pos) { m_relativePosition = pos; }

private:
	VectorF m_relativePosition;

	friend std::ostream& operator<< (std::ostream& os, RelativePositionComponent const& c);
	friend std::ostream& operator<< (std::ostream& os, RelativePositionComponent const* pC);
};

#endif