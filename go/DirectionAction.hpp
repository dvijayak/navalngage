#ifndef DirectionAction_hpp
#define DirectionAction_hpp

#include "Action.hpp"
#include "VectorF.hpp"

class DirectionAction : virtual public Action
{
public:
	DirectionAction () : Action() {}
	~DirectionAction () {}

	/// Action
	void Perform ();
	std::string str () const;

	void SetDirection (float const theta) { m_direction = theta; }

private:
	float m_direction;
};

#endif