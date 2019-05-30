#include "Action.hpp"

#include "global.hpp"
#include <sstream>

#include "ActionReplay.hpp"

Action::Action (GameObject* pSource, GameObject* pTarget)
	: m_pSource(pSource)
	, m_pTarget(pTarget)
	, m_ticksCreated(Chrono::GetTicks())
{
}

// Default implementation
void Action::Perform ()
{
	m_ticksPerformed = Chrono::GetTicks(); // CANIMPROVE: is millisecond precision too imprecise?
	// console("{}", *this);
	trclog("{}", *this);

	// TODO: Record action
}

std::string Action::str () const
{
	std::stringstream ss;
	ss << m_ticksPerformed;
	return ss.str();
}

std::string Action::str_base () const
{
	std::stringstream ss;
	if (m_pSource)
		ss << STR_SEP << "source=" << m_pSource->GetSuid();
	if (m_pTarget)
		ss << STR_SEP << "target=" << m_pTarget->GetSuid();
	return ss.str();
}