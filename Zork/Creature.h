#ifndef __Creature__
#define __Creaturer__

#include "Entity.h"

class Room;

class Creature : public Entity
{
public:
	Creature();
	Creature(string pName, Room* pActualLocation);
	~Creature();

protected:
	string name;
	Room* actualLocation;

private:
};

#endif //__Creature__