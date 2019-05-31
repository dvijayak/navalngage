#include "RotateAction.hpp"

#include <cmath>
#include <sstream>

#include "RotationComponent.hpp"
#include "BodyComponent.hpp"

void RotateAction::Perform ()
{
	Action::Perform();

	assert(m_pSource);

	if (!m_pSource->Has<CRotation>()) return;

	// TODO: Mass affects angle increment?

	// Update object's rotation/direction	
	float const current = m_pSource->Get<CRotation>().GetRotationAngle();
	m_pSource->Get<CRotation>().SetRotationAngle(current + m_theta);
}

std::string RotateAction::str () const
{
	std::stringstream ss;
	ss << Action::str() << STR_SEP << "RotateAction";
	ss << Action::str_base();
	ss << STR_SEP << "theta=" << m_theta;
	return ss.str();
}