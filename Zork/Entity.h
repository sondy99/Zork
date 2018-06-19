#ifndef __Entity__
#define __Entity__

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

class World;

using namespace std;

enum EntityType
{
	ENTITY,
	ROOM,
	EXIT,
	ITEM,
	CREATURE,
	ENEMY,
	PLAYER
};

class Entity
{
public:
	Entity();
	Entity(string pName ,string pDescription);
	~Entity();

	string GetName();
	World* GetWorld();
	void PrintName();
	string GetDescription();
	void PrintDescription();

protected:
	World* world;
	string name;
	string description;

private:
};

#endif //__Entity__
