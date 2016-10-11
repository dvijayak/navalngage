#ifndef PositionComponent_HPP
#define PositionComponent_HPP

#include "IComponent.hpp"

struct PositionComponent
	: virtual public IComponent
{
	static const IComponent::Name NAME;

	PositionComponent (float _x = 0.0f, float _y = 0.0f)
		: x(_x), y(_y)
	{}
	~PositionComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	float x;
	float y;
};
const IComponent::Name PositionComponent::NAME = "PositionComponent";

#endif