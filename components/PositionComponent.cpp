#include "PositionComponent.hpp"

std::ostream& operator<< (std::ostream& os, PositionComponent const& c)
{
	os << "[ PositionComponent: ";
	os << "position = " << c.m_position;
	os << " ]";
	return os;
}

std::ostream& operator<< (std::ostream& os, PositionComponent const* pC)
{
	if (!pC)
	{
		os << "[ PositionComponent: (Null) ]";
	}
	else
	{
		os << *pC;
	}
	return os;
}