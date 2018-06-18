#include "Creature.h"

Creature::Creature()
{
}

Creature::Creature(string pName, Room* pActualLocation)
{
	name = pName;
	actualLocation = pActualLocation;
}

Creature::~Creature()
{
}