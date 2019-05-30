#include "ShipBuilder.hpp"

#include "ShipComponent.hpp"
#include "MassComponent.hpp"

ShipBuilder::ShipBuilder ()
{}

ShipBuilder::~ShipBuilder ()
{}

void ShipBuilder::MakeDefault ()
{
	MovableBuilder::MakeDefault();

	AddShip(ShipComponent::Class::SLOOP);
	AddMass(10.0); // TODO: Vary mass based on ship class

	// Note that a body isn't created by default!
}

void ShipBuilder::AddShip (int ship_class)
{
	m_components.push_back(new ShipComponent(ship_class));
}

// TODO: Vary mass based on ship class
void ShipBuilder::AddMass (float mass)
{
	m_components.push_back(new MassComponent(mass));
}