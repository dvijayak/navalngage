#include "MassComponent.hpp"

const IComponent::Name MassComponent::NAME = "MassComponent";

std::ostream& operator<< (std::ostream& os, MassComponent const& c)
{
	os << "[ MassComponent: ";
	os << "mass = " << c.m_mass;
	os << " ]";
	return os;
}

std::ostream& operator<< (std::ostream& os, MassComponent const* pC)
{
	if (!pC)
	{
		os << "[ MassComponent: (Null) ]";
	}
	else
	{
		os << *pC;
	}
	return os;
}