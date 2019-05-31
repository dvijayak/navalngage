#ifndef ShipComponent_hpp
#define ShipComponent_hpp

#include "IComponent.hpp"

#include <ostream>

DEFINE_COMPONENT(Ship)
{
public:
	static const IComponent::Name NAME;

	enum Class
	{
		SLOOP,
		FRIGATE,
		MANOFWAR
	};

	ShipComponent (int klass = SLOOP) : m_class(klass)	{}
	~ShipComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	int GetShipClass () const { return m_class; }
	void SetShipClass (int klass) { m_class = klass; }

private:
	int m_class;

	friend std::ostream& operator<< (std::ostream& os, ShipComponent const& c);
	friend std::ostream& operator<< (std::ostream& os, ShipComponent const* pC);
};

#endif