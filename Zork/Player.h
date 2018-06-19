#ifndef __Player__
#define __Player__

#include "Creature.h"
#include "Item.h"

class Worl;
class Room;
class Item;

class Player : public Creature
{
public:
	Player();
	Player(string pName, Room* pActualLocation, World* pWorld, int pHitpoints, int pMaxHit = 1);
	~Player();

	void Go(string pDirection);
	void Take(string pItem);
	void Use(string pItem);
	void Drop(string pItem);
	void Look();
	void PrintInventory();
	void Attack(string pCreatureName);

private:

};

#endif //__Player__
