#ifndef ShipComponent_hpp
#define ShipComponent_hpp

#include "IComponent.hpp"

struct ShipComponent
	: virtual public IComponent
{
	static const IComponent::Name NAME;

	enum Class
	{
		SWOOP,
		FRIGATE,
		MANOFWAR
	};

	ShipComponent (int klass = SWOOP)
		: ship_class(klass)
	{}
	~ShipComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	int ship_class;
};
const IComponent::Name ShipComponent::NAME = "ShipComponent";

#endif