#include "Item.h"

Item::Item()
{
}

Item::Item(string pName, string pDescription)
{
	name = pName;
	description = pDescription;
	type = COMMON;
}

Item::Item(string pName, string pDescription, ItemType pType)
{
	name = pName;
	description = pDescription;
	type = pType;
}

Item::Item(string pName, string pDescription, ItemType pType, int pAtk, int pDef)
{
	name = pName;
	description = pDescription;
	type = pType;
	atk = pAtk;
	def = pDef;
}

Item::~Item()
{
}

ItemType Item::GetItemType()
{
	return type;
}

int Item::GetAtk()
{
	return atk;
}

int Item::GetDef()
{
	return def;
}

void Item::SetNote(string pNote)
{
	note = pNote;
}

Item* Item::GetItemInside()
{
	Item* resutl = itemInside;
	itemInside = nullptr;
	return resutl;
}

void Item::PutItemInside(Item* pItem)
{
	itemInside = pItem;
}

string Item::GetNote()
{
	return note;
}

string Item::PrintStats()
{
	return name + " / atk:" + to_string(atk) + " def: " + to_string(def);
}

bool Item::IsPosibleToTake()
{
	return posibleToTake;
}

void Item::SetPosibleToTake(bool pPosibleToTake)
{
	posibleToTake = pPosibleToTake;
}
