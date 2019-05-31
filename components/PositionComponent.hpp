#ifndef PositionComponent_HPP
#define PositionComponent_HPP

#include "IComponent.hpp"
#include "VectorF.hpp"

#include <ostream>

DEFINE_COMPONENT(Position)
{
public:
	static const IComponent::Name NAME;

	PositionComponent (float x = 0.0f, float y = 0.0f) : m_position(x, y) {}
	PositionComponent (VectorF const& pos) : m_position(pos) {}
	~PositionComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	VectorF const& GetPosition () const { return m_position; }
	VectorF& GetPosition () { return m_position; }
	void SetPosition (VectorF const& pos) { m_position = pos; }

private:
	VectorF m_position;

	friend std::ostream& operator<< (std::ostream& os, PositionComponent const& c);
	friend std::ostream& operator<< (std::ostream& os, PositionComponent const* pC);
};

#endif