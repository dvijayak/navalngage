#ifndef RelativePositionComponent_HPP
#define RelativePositionComponent_HPP

#include "IComponent.hpp"
#include "VectorF.hpp"

#include <ostream>

/// Position is relative to another object's position. That is, it exists in a 
/// coordinate space where the associated position is the origin (0,0).

DEFINE_COMPONENT(RelativePosition)
{
public:
	static const IComponent::Name NAME;

	RelativePositionComponent (float x = 0.0f, float y = 0.0f) : m_relativePosition(x, y) {}
	RelativePositionComponent (VectorF const& pos) : m_relativePosition(pos) {}
	~RelativePositionComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	VectorF const& GetRelativePosition () const { return m_relativePosition; }
	VectorF& GetRelativePosition () { return m_relativePosition; }
	void SetRelativePosition (VectorF const& pos) { m_relativePosition = pos; }

private:
	VectorF m_relativePosition;

	friend std::ostream& operator<< (std::ostream& os, RelativePositionComponent const& c);
	friend std::ostream& operator<< (std::ostream& os, RelativePositionComponent const* pC);
};

#endif