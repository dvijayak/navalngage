#include "MovableBuilder.hpp"

#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "BodyComponent.hpp"

MovableBuilder::MovableBuilder ()
{}

MovableBuilder::~MovableBuilder ()
{}

void MovableBuilder::MakeDefault ()
{
	AddPosition(VectorF());
	AddMovement(VectorF(0.0, 1.0), 0.0, 30.0);

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

void MovableBuilder::AddMovement (VectorF const& direction, float speed, float maxSpeed)
{
	m_components.push_back(new MovementComponent(direction, speed, maxSpeed));
}

void MovableBuilder::AddBody (PolygonF const& poly, Uint32 color)
{
	m_components.push_back(new BodyComponent(poly, color));
}