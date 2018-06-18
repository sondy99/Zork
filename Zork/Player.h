#ifndef __Player__
#define __Player__

#include "Creature.h"
#include "Item.h"

class Room;
class Item;

class Player : public Creature
{
public:
	Player();
	Player(string pName, Room* pActualLocation, int pHitpoints);
	~Player();

	void Go(string pDirection);
	void Take(string pItem);
	void Use(string pItem);
	void Drop(string pItem);
	void Look();
	void PrintInventory();

private:

};

#endif //__Player__
