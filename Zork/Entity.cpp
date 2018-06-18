#include "Entity.h"

Entity::Entity() 
{
}

Entity::Entity(string pName, string pDescription)
{
	name = pName;
	description = pDescription;
}

Entity::~Entity()
{
}

string Entity::GetName()
{
	return name;
}

void Entity::PrintName()
{
	cout << name << endl;
}

string Entity::GetDescription()
{
	return description;
}

void Entity::PrintDescription()
{
	cout << description << endl;
}