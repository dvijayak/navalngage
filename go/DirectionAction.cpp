#include "DirectionAction.hpp"

#include <sstream>

#include "RotationComponent.hpp"

#include "MathUtil.hpp"

void DirectionAction::Perform ()
{
	Action::Perform();

	assert(m_pSource);

	if (!m_pSource->Has<RotationComponent>()) return;

	m_pSource->Get<RotationComponent>().SetRotationAngle(m_direction);
}

std::string DirectionAction::str () const
{
	std::stringstream ss;
	ss << Action::str() << STR_SEP << "DirectionAction";
	ss << Action::str_base();
	ss << STR_SEP << "direction=" << MathUtil::RadiansToDegrees(m_direction) << "°";
	return ss.str();
}