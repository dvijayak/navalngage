#ifndef RotationComponent_hpp
#define RotationComponent_hpp

#include "IComponent.hpp"

struct RotationComponent
	: virtual public IComponent
{
	static const IComponent::Name NAME;

	RotationComponent (float omega = 0.0f)
		: angular_speed(omega)
	{}
	~RotationComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	float angular_speed;
};
const IComponent::Name RotationComponent::NAME = "RotationComponent";

#endif