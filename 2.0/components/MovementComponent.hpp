#ifndef MovementComponent_hpp
#define MovementComponent_hpp

#include "IComponent.hpp"

struct MovementComponent
	: virtual public IComponent
{
	static const IComponent::Name NAME;

	MovementComponent (float _speed = 0.0f, float _heading = 0.0f)
		: speed(_speed), heading(_heading)
	{}
	~MovementComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	float speed;
	float heading; // 0 - 359 degrees
};
const IComponent::Name MovementComponent::NAME = "MovementComponent";

#endif