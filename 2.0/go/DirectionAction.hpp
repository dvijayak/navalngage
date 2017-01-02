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

	void SetDirection (VectorF const& v) { m_direction = v; }

private:
	VectorF m_direction;
};

#endif