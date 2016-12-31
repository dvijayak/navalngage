#ifndef RotateAction_HPP
#define RotateAction_HPP

#include "SpeedAction.hpp"
#include "MovementComponent.hpp"

#include "MatrixF.hpp"

#include <cmath>

class RotateAction : virtual public Action
{
public:
	RotateAction () : Action(), m_theta(0) {}
	~RotateAction () {}

	/// Angle is in radians
	void SetAngle (float theta) { m_theta = theta; }

	/// Action
	void Perform ();

private:
	float m_theta;
};

void RotateAction::Perform ()
{
	Action::Perform();

	assert(m_pSource);

	if (!m_pSource->HasComponent<MovementComponent>()) return;

	// TODO: Mass affects angle increment?

	float cos_theta = std::cos(m_theta);
	float sin_theta = std::sin(m_theta);
	Matrix2F rot{{cos_theta, -sin_theta,
					  sin_theta, cos_theta}};

	VectorF const& dir = m_pSource->GetComponent<MovementComponent>()->GetDirection();
	ColMatrix2F res = rot * ColMatrix2F(dir);
	VectorF newDir(res[0], res[1]);
	m_pSource->GetComponent<MovementComponent>()->SetDirection(newDir);
}

#endif