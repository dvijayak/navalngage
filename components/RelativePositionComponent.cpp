#include "RelativePositionComponent.hpp"

const IComponent::Name RelativePositionComponent::NAME = "RelativePositionComponent";

std::ostream& operator<< (std::ostream& os, RelativePositionComponent const& c)
{
	os << "[ RelativePositionComponent: ";
	os << "relative position = " << c.m_relativePosition;
	os << " ]";
	return os;
}

std::ostream& operator<< (std::ostream& os, RelativePositionComponent const* pC)
{
	if (!pC)
	{
		os << "[ RelativePositionComponent: (Null) ]";
	}
	else
	{
		os << *pC;
	}
	return os;
}