#ifndef __Item__
#define __Item__

#include "Entity.h"

enum ItemType
{
	COMMON,
	WEAPON,
	ARMOUR
};

class Item : public Entity
{
public:
	Item();
	Item(string pName, string pDescription);
	Item(string pName, string pDescription, ItemType pType, int pAtk, int pDef);
	~Item();

	ItemType GetItemType();
	int GetAtk();
	int GetDef();
	string PrintStats();
private:
	ItemType type;
	int atk = 0;
	int def = 0;
};

#endif //__Item__
