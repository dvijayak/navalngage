#ifndef Action_hpp
#define Action_hpp

#include <string>

#include "GameObject.hpp"

#include "Chrono.hpp"

class Action
{
public:
	Action (GameObject* pSource=0, GameObject* pTarget=0);
	virtual ~Action () {}

	virtual void Perform () = 0;

	virtual std::string str () const = 0;

	virtual void SetSource (GameObject* pGo) { m_pSource = pGo; }
	virtual void SetTarget (GameObject* pGo) { m_pTarget = pGo; }

protected:
	std::string str_base () const;

	GameObject* m_pSource;
	GameObject* m_pTarget;

	Chrono::Tick m_ticksCreated;
	Chrono::Tick m_ticksPerformed;

	static constexpr char STR_SEP = ',';
};

inline std::ostream& operator<< (std::ostream& os, Action const& a)
{
	return os << a.str();
}

#endif