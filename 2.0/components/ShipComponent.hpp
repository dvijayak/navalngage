#ifndef ShipComponent_hpp
#define ShipComponent_hpp

#include "IComponent.hpp"

class ShipComponent
	: virtual public IComponent
{
public:
	static const IComponent::Name NAME;

	enum Class
	{
		SWOOP,
		FRIGATE,
		MANOFWAR
	};

	ShipComponent (int klass = SWOOP) : m_class(klass)	{}
	~ShipComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	int GetShipClass () const { return m_class; }
	void SetShipClass (int klass) { m_class = klass; }

private:
	int m_class;
};
const IComponent::Name ShipComponent::NAME = "ShipComponent";

#endif