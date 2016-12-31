#ifndef SpeedAction_HPP
#define SpeedAction_HPP

#include "Action.hpp"
#include "MovementComponent.hpp"

#include "global.hpp"

class SpeedAction : virtual public Action
{
public:
	enum ChangeType
	{
		REPLACE=0, // the speed is the target value
		ADJUST // the speed is an increment/decrement value 
	};

	SpeedAction () : Action(), m_speed(0.0), m_changeType(REPLACE) {}
	~SpeedAction () {}

	/// Action
	void Perform ();

	void SetSpeed (float val) { m_speed = val; }
	void SetChangeType (ChangeType type) { m_changeType = (int)type; };

protected:
	float m_speed;
	int m_changeType;
};

void SpeedAction::Perform ()
{
	Action::Perform();

	assert(m_pSource);

	if (!m_pSource->HasComponent<MovementComponent>()) return;

	// TODO: Mass affects velocity increment, but this needs to be handled at the command level, i.e. the point of state change
	// TODO: Should mass affect max speed?

	if (m_changeType == REPLACE)
	{
		m_pSource->GetComponent<MovementComponent>()->SetSpeed(m_speed);
	}
	else if (m_changeType == ADJUST)
	{
		if (m_speed != 0.0)
		{
			// MovementComponent takes care of speed bounds
			float speed = m_pSource->GetComponent<MovementComponent>()->GetSpeed();
			float target = speed + m_speed;
			m_pSource->GetComponent<MovementComponent>()->SetSpeed(target);
		}
	}
}

#endif