#include "RotateAction.hpp"

#include <cmath>
#include <sstream>

#include "MovementComponent.hpp"
#include "BodyComponent.hpp"

#include "MatrixF.hpp"

void RotateAction::Perform ()
{
	Action::Perform();

	assert(m_pSource);

	if (!m_pSource->Has<CMovement>()) return;

	// TODO: Mass affects angle increment?
	
	// Apply rotation on the object's direction vector
	VectorF const& dir = m_pSource->Get<CMovement>().GetDirection();
	m_pSource->Get<CMovement>().SetDirection(dir.Rotate(m_theta));

	// Apply rotation on the object's surface polygon, if any
	if (m_pSource->Has<CBody>())
	{
		for (auto& v : m_pSource->Get<CBody>().GetSurface().vertices)
		{
			v = v.Rotate(m_theta);
		}
	}
}

std::string RotateAction::str () const
{
	std::stringstream ss;
	ss << Action::str() << STR_SEP << "RotateAction";
	ss << Action::str_base();
	ss << STR_SEP << "theta=" << m_theta;
	return ss.str();
}