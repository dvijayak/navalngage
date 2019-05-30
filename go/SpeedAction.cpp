#include "SpeedAction.hpp"

#include <sstream>
#include "MovementComponent.hpp"

void SpeedAction::Perform ()
{
	Action::Perform();

	assert(m_pSource);

	if (!m_pSource->Has<MovementComponent>()) return;

	// TODO: Mass affects velocity increment, but this needs to be handled at the command level, i.e. the point of state change
	// TODO: Should mass affect max speed?

	if (m_changeType == REPLACE)
	{
		m_pSource->Get<MovementComponent>().SetSpeed(m_speed);
	}
	else if (m_changeType == ADJUST)
	{
		if (m_speed != 0.0)
		{
			// MovementComponent takes care of speed bounds
			float speed = m_pSource->Get<MovementComponent>().GetSpeed();
			float target = speed + m_speed;
			m_pSource->Get<MovementComponent>().SetSpeed(target);
		}
	}
}

std::string SpeedAction::str () const
{
	std::stringstream ss;
	ss << Action::str() << STR_SEP << "SpeedAction";
	ss << Action::str_base();
	ss << STR_SEP << "speed=" << m_speed;
	ss << STR_SEP << "changeType=" << m_changeType;
	return ss.str();
}