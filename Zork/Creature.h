#ifndef __Creature__
#define __Creaturer__

#include "Entity.h"

class Room;
class Item;

class Creature : public Entity
{
public:
	Creature();

	
	~Creature();

	void Equip(string pItemName);
	void Unequip(string pItemName);
	int CalculateDamage();
	void TakeDamage(int pDamage);
	bool IsAlive();
	void Stats();
	Room* GetCurrenLocation();

protected:
	Room* currentLocation;
	EntityType entityType;
	int hitpoints;
	int atk = 0;
	int def = 0;
	int maxHit = 4;
	Item* rightHand = nullptr;
	Item* leftHand = nullptr;
	Item* armor = nullptr;
	vector<Item*> inventory;

	Item* GetItemFromInventory(string pName);
	void IntroduceItemInTheInventory(Item* pItem);
	void RemoveItemFromInventory(Item* pItem);
	void ManageStats();

private:
};

#endif //__Creature__