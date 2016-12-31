#ifndef RotateAction_HPP
#define RotateAction_HPP

#include "SpeedAction.hpp"
#include "MovementComponent.hpp"
#include "BodyComponent.hpp"

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

	if (!m_pSource->Has<CMovement>()) return;

	// TODO: Mass affects angle increment?

	// Compute the rotation matrix
	float cos_theta = std::cos(m_theta);
	float sin_theta = std::sin(m_theta);
	Matrix2F rot{{cos_theta, -sin_theta,
					  sin_theta, cos_theta}};
	
	// Apply rotation on the object's direction
	VectorF const& dir = m_pSource->Get<CMovement>().GetDirection();
	ColMatrix2F res = rot * ColMatrix2F(dir);
	m_pSource->Get<CMovement>().SetDirection(Vector2F(res[0], res[1]));

	// Apply rotation on the object's surface polygon, if any
	if (m_pSource->Has<CBody>())
	{
		ColMatrix2F res;
		for (auto& v : m_pSource->Get<CBody>().GetSurface().vertices)
		{
			res = rot * ColMatrix2F(Vector2F(v.x, v.y));
			v.x = res[0];
			v.y = res[1];
		}
	}
}

#endif