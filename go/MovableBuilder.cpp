#include "MovableBuilder.hpp"

#include "PositionComponent.hpp"
#include "SpeedComponent.hpp"
#include "RotationComponent.hpp"
#include "BodyComponent.hpp"

#include "MathUtil.hpp"

MovableBuilder::MovableBuilder ()
{}

MovableBuilder::~MovableBuilder ()
{}

void MovableBuilder::MakeDefault ()
{
	AddPosition(VectorF());
   AddSpeed(0.0, 30.0);
	AddRotation(MathUtil::DegreesToRadians(90));

	// Note that a body isn't created by default!
}

void MovableBuilder::AddPosition (float x, float y)
{
	AddPosition(VectorF(x, y));
}

void MovableBuilder::AddPosition (VectorF const& pos)
{
	m_components.push_back(new PositionComponent(pos));
}

void MovableBuilder::AddSpeed (float speed, float maxSpeed)
{
   m_components.push_back(new SpeedComponent(speed, maxSpeed));
}

void MovableBuilder::AddRotation (float theta)
{
	m_components.push_back(new RotationComponent(theta));
}

void MovableBuilder::AddBody (PolygonF const& poly, Uint32 color)
{
	m_components.push_back(new BodyComponent(poly, color));
}