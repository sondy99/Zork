#ifndef __Entity__
#define __Entity__

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

enum EntityType
{
	ENTITY,
	ROOM,
	EXIT,
	ITEM,
	CREATURE,
	PLAYER
};

class Entity
{
public:
	Entity();
	Entity(string pName ,string pDescription);
	~Entity();

	string GetName();
	void PrintName();
	string GetDescription();
	void PrintDescription();

protected:
	string name;
	string description;

private:
};

#endif //__Entity__
