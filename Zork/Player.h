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
	Player(string pName, string pDescription, Room* pActualLocation, World* pWorld, int pHitpoints, int pMaxHit = 1);
	~Player();

	void Go(string pDirection);
	void Take(string pItem);
	void Use(string pItem, string pDirection);
	void Drop(string pItem);
	void Open(string pItem);
	void Read(string pItem);
	void Look(bool pByCommand);
	void PrintInventory();
	void Attack(string pCreatureName);

private:

};

#endif //__Player__
