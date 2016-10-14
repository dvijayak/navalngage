#ifndef PositionComponent_HPP
#define PositionComponent_HPP

#include "IComponent.hpp"
#include "Vector2F.hpp"

class PositionComponent
	: virtual public IComponent
{
public:
	static const IComponent::Name NAME;

	PositionComponent (float x = 0.0f, float y = 0.0f) : m_position(x, y) {}
	PositionComponent (Vector2F const& pos) : m_position(pos) {}
	~PositionComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	Vector2F const& GetPosition () const { return m_position; }
	Vector2F& GetPositionMod () { return m_position; }
	void SetPosition (Vector2F const& pos) { m_position = pos; }

private:
	Vector2F m_position;
};
const IComponent::Name PositionComponent::NAME = "PositionComponent";

#endif