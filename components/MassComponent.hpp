#ifndef MassComponent_hpp
#define MassComponent_hpp

#include "IComponent.hpp"

#include <ostream>

DEFINE_COMPONENT(Mass)
{
public:
	static const IComponent::Name NAME;

	MassComponent (float mass = 0.0f)
		: m_mass(mass)
	{}
	~MassComponent () {}

	/// IComponent
	IComponent::Name GetName () const { return NAME; }

	float GetMass () const { return m_mass; }
	void SetMass (float mass) { m_mass = mass; }

private:
	float m_mass; // kgs

	friend std::ostream& operator<< (std::ostream& os, MassComponent const& c);
	friend std::ostream& operator<< (std::ostream& os, MassComponent const* pC);
};

#endif