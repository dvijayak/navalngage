#include "DirectionAction.hpp"

#include <sstream>

#include "MovementComponent.hpp"

void DirectionAction::Perform ()
{
	Action::Perform();

	assert(m_pSource);

	if (!m_pSource->Has<MovementComponent>()) return;

	m_pSource->Get<MovementComponent>().SetDirection(m_direction);
}

std::string DirectionAction::str () const
{
	std::stringstream ss;
	ss << Action::str() << STR_SEP << "DirectionAction";
	ss << Action::str_base();
	ss << STR_SEP << "x=" << m_direction.GetX();
	ss << STR_SEP << "y=" << m_direction.GetY();
	return ss.str();
}