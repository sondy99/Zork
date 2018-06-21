#include "Room.h"
#include "Creature.h"

Room::Room()
{
}

Room::Room(string pName, string pDescription)
{
	name = pName;
	description = pDescription;
}

Room::Room(string pName, string pDescription, bool pFinalRoom)
{
	name = pName;
	description = pDescription;
	finalRoom = pFinalRoom;
}
Room::~Room()
{
}

string Room::GetDescription(bool forced)
{
	string result = "";

	if (!alreadyBeenHere || forced)
	{
		result = description;
		alreadyBeenHere = true;
	}

	return result;
}

bool Room::IsAlreadyBeenHere(){
	return alreadyBeenHere;
}

void Room::AddLocation(string pDirection, Room* pRoom)
{
	Location location;
	location.direction = pDirection;
	location.room = pRoom;

	locations.push_back(location);
}

void Room::AddLocation(string pDirection, Room* pRoom, bool pLocked, Item* pItem, string pMessage)
{
	Location location;
	location.direction = pDirection;
	location.room = pRoom;
	location.locked = pLocked;
	location.message = pMessage;

	if (pLocked && pItem != nullptr)
	{
		location.item = pItem;
	}

	locations.push_back(location);
}

void Room::AddLocation(string pDirection, Room* pRoom, bool pLocked, string pMessage)
{
	Location location;
	location.direction = pDirection;
	location.room = pRoom;
	location.locked = pLocked;
	location.message = pMessage;

	locations.push_back(location);
}

Room* Room::GoTo(string pDirection, EntityType pEntityType, bool pWwin)
{
	Room* result = nullptr;
	bool locked = false;

	for (unsigned int i = 0; i < locations.size(); i++) 
	{
		if (locations[i].direction == pDirection)
		{
			if ((!locations[i].locked && !locations[i].room->GetFinalRoom())  || (locations[i].room->GetFinalRoom() && pWwin))
			{
				result = locations[i].room;
			}
			else
			{
				if (pEntityType == PLAYER)
				{
					string message = locations[i].message == "" ? "The door is locked." : locations[i].message;
					cout << message << endl;
				}
				locked = true;
			}
		}
	}

	if (result == nullptr && !locked && pEntityType == PLAYER)
	{
		cout << "There is no place to go that way." << endl;
	}

	return result;
}

Item* Room::TakeItem(string pItem)
{

	Item* result = nullptr;
	int itemIdex = -1;

	for (unsigned int i = 0; i < items.size(); i++) 
	{
		
		if (items.at(i)->GetName() == pItem)
		{
			if (items.at(i)->IsPosibleToTake())
			{
				result = items.at(i);
			}
			itemIdex = i;
		}
	}

	if (itemIdex != -1 && items.at(itemIdex)->GetName() == pItem && !items.at(itemIdex)->IsPosibleToTake())
	{
		cout << "Is not possible to take this item." << endl;
	}
	else if(result == nullptr)
	{
		cout << "There is no item named like that " << pItem  << "."<< endl;
	}
	else if (result != nullptr)
	{
		items.erase(items.begin() + itemIdex);
	}

	return result;
}

Item * Room::GetItem(string pItem)
{
	Item* result = nullptr;

	for (unsigned int i = 0; i < items.size(); i++)
	{
		if (items.at(i)->GetName() == pItem)
		{
			result = items.at(i);
			
		}
	}

	return result;
}

vector<Item*> Room::GetItems()
{
	return items;
}

void Room::AddItem(Item* pItem)
{
	items.push_back(pItem);
}

void Room::DropItem(Item * pItem)
{
	items.push_back(pItem);
}

void Room::UseItem(string pItem, string pDirection)
{
	bool usedItem = false;
	for (unsigned int i = 0; i < locations.size(); i++)
	{
		if (locations[i].item != nullptr && locations[i].item->GetName() == pItem && locations[i].direction == pDirection)
		{
			locations[i].locked = !locations[i].locked;
			cout << pItem << " was used on " << locations[i].direction << endl;
			usedItem = true;
			break;
		}
	}

	if (!usedItem)
	{
		cout << pItem << " is not useful here." << endl;
	}
}

bool Room::GetFinalRoom()
{
	return finalRoom;
}
