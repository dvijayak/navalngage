#include "ShipBuilder.hpp"

#include "global.hpp"

#include "GameObject.hpp"
#include "GameObjectFactory.hpp"

#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "RotationComponent.hpp"
#include "ShipComponent.hpp"
#include "MassComponent.hpp"
#include "BodyComponent.hpp"

ShipBuilder::ShipBuilder (GameObjectFactory& factory)
	: m_pGo(&(factory.Create(false))) // CANIMPROVE: change GOFactory::Create API to return pointer instead? What's the value in returning a reference, anyway?
	, m_bConstructionCompleted(false)
{
	assert(m_pGo);
}

ShipBuilder::~ShipBuilder ()
{
	// Free up allocation if construction is still in progress
	if (!m_bConstructionCompleted)
	{
		delete m_pGo;
	}
}

void ShipBuilder::MakeDefault ()
{
	AddPosition(VectorF());
	AddMovement(VectorF());
	AddRotation(0.0);
	AddShip(ShipComponent::Class::SLOOP);
	AddMass(10.0); // TODO: Control mass based on ship class

	// Note that a body isn't created by default!
}

void ShipBuilder::AddPosition (float x, float y)
{
	AddPosition(VectorF(x, y));
}

void ShipBuilder::AddPosition (VectorF const& pos)
{
	if ( !(m_pGo->AddComponent(new PositionComponent(pos))) )
	{
		errlog("Failed to add position component to object " << *m_pGo << " using parameters: " << pos);
	}
}

void ShipBuilder::AddMovement (VectorF const& velocity)
{
	if ( !(m_pGo->AddComponent(new MovementComponent(velocity))) )
	{
		errlog("Failed to add movement component to object " << *m_pGo << " using parameters: " << velocity);
	}
}

void ShipBuilder::AddRotation (float angular_speed)
{
	if ( !(m_pGo->AddComponent(new RotationComponent(angular_speed))) )
	{
		errlog("Failed to add rotation component to object " << *m_pGo << " using parameters: angular_speed = " << angular_speed);
	}
}

void ShipBuilder::AddShip (int ship_class)
{
	if ( !(m_pGo->AddComponent(new ShipComponent(ship_class))) )
	{
		errlog("Failed to add ship component to object " << *m_pGo << " using parameters: ship class/type = " << ship_class);
	}
}

void ShipBuilder::AddMass (float mass)
{
	if ( !(m_pGo->AddComponent(new MassComponent(mass))) )
	{
		errlog("Failed to add mass component to object " << *m_pGo << " using parameters: mass = " << mass);
	}
}

void ShipBuilder::AddBody (PolygonF const& poly, Uint32 color)
{
	if ( !(m_pGo->AddComponent(new BodyComponent(poly, color))) )
	{
		errlog("Failed to add body component to object " << *m_pGo << " using parameters: polygon = " << poly << ", color = " << color);
	}	
}

GameObject* ShipBuilder::GetResult ()
{
	assert(!m_bConstructionCompleted); // a builder instance may not be re-used
	m_bConstructionCompleted = true;
	return m_pGo;
}