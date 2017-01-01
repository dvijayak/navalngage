#include "ShipComponent.hpp"

const IComponent::Name ShipComponent::NAME = "ShipComponent";

std::ostream& operator<< (std::ostream& os, ShipComponent const& c)
{
	os << "[ ShipComponent: ";
	os << "class = ";
	switch (c.m_class)
	{
		case ShipComponent::SLOOP:
			os << "Sloop";
			break;
		case ShipComponent::FRIGATE:
			os << "Frigate";
			break;
		case ShipComponent::MANOFWAR:
			os << "Man-of-war";
			break;
		default:
			os << "(Unknown)";
			break;
	}
	os << " ]";
	return os;
}

std::ostream& operator<< (std::ostream& os, ShipComponent const* pC)
{
	if (!pC)
	{
		os << "[ ShipComponent: (Null) ]";
	}
	else
	{
		os << *pC;
	}
	return os;
}