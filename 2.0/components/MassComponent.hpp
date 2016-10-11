#ifndef MassComponent_hpp
#define MassComponent_hpp

#include "IComponent.hpp"

struct MassComponent
	: virtual public IComponent
{
	static const IComponent::Name NAME;

	MassComponent (float _mass = 0.0f)
		: mass(_mass)
	{}
	~MassComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	float mass; // kgs
};
const IComponent::Name MassComponent::NAME = "MassComponent";

#endif