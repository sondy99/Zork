#ifndef __Item__
#define __Item__

#include "Entity.h"

enum ItemType
{
	COMMON,
	WEAPON,
	ARMOUR,
	READABLE,
	CONTAINER
};

class Item : public Entity
{
public:
	Item();
	Item(string pName, string pDescription);
	Item(string pName, string pDescription, ItemType pType);
	Item(string pName, string pDescription, ItemType pType, int pAtk, int pDef);
	~Item();

	ItemType GetItemType();
	int GetAtk();
	int GetDef();
	void SetNote(string pNote);
	Item* GetItemInside();
	void PutItemInside(Item* pItem);
	string GetNote();
	string PrintStats();
	bool IsPosibleToTake();
	void SetPosibleToTake(bool pPosibleToTake);

private:
	ItemType type;
	int atk = 0;
	int def = 0;
	string note = "";
	Item* itemInside = nullptr;
	bool posibleToTake = true;
};

#endif //__Item__
