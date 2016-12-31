#ifndef DirectionAction_hpp
#define DirectionAction_hpp

#include "Action.hpp"
#include "MovementComponent.hpp"

#include "VectorF.hpp"

class DirectionAction : virtual public Action
{
public:
	DirectionAction () : Action() {}
	~DirectionAction () {}

	/// Action
	void Perform ();

	void SetDirection (VectorF const& v) { m_direction = v; }

private:
	VectorF m_direction;
};

void DirectionAction::Perform ()
{
	Action::Perform();

	assert(m_pSource);

	if (!m_pSource->Has<MovementComponent>()) return;

	m_pSource->Get<MovementComponent>().SetDirection(m_direction);
}

#endif