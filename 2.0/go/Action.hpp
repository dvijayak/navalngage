#ifndef Action_hpp
#define Action_hpp

#include "GameObject.hpp"

class Action
{
public:
	Action (GameObject* pSource=0, GameObject* pTarget=0) : m_pSource(pSource), m_pTarget(pTarget) {}
	virtual ~Action () {}

	virtual void Perform () = 0;

	virtual void SetSource (GameObject* pGo) { m_pSource = pGo; }
	virtual void SetTarget (GameObject* pGo) { m_pTarget = pGo; }

protected:
	GameObject* m_pSource;
	GameObject* m_pTarget;

// TODO: time created, time performed
//private:
};

#endif