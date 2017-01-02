#ifndef RotateAction_HPP
#define RotateAction_HPP

#include "Action.hpp"

class RotateAction : virtual public Action
{
public:
	RotateAction () : Action(), m_theta(0) {}
	~RotateAction () {}

	/// Angle is in radians
	void SetAngle (float theta) { m_theta = theta; }

	/// Action
	void Perform ();
	std::string str () const;

private:
	float m_theta;
};

#endif