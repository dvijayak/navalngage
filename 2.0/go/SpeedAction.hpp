#ifndef SpeedAction_hpp
#define SpeedAction_hpp

#include "Action.hpp"

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
	std::string str () const;

	void SetSpeed (float val) { m_speed = val; }
	void SetChangeType (ChangeType type) { m_changeType = (int)type; };

private:
	float m_speed;
	int m_changeType;
};

#endif