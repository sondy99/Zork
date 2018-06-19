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

Room::~Room()
{
}

void Room::AddLocation(string pDirection, Room* pRoom)
{
	Location location;
	location.direction = pDirection;
	location.room = pRoom;

	locations.push_back(location);
}

void Room::AddLocation(string pDirection, Room* pRoom, bool pLocked, Item* pItem)
{
	Location location;
	location.direction = pDirection;
	location.room = pRoom;
	location.locked = pLocked;

	if (pLocked && pItem != nullptr)
	{
		location.item = pItem;
	}

	locations.push_back(location);
}

Room* Room::GoTo(string pDirection, EntityType pEntityType)
{
	Room* result = nullptr;
	bool locked = false;

	for (unsigned int i = 0; i < locations.size(); i++) 
	{
		if (locations[i].direction == pDirection)
		{
			if (!locations[i].locked)
			{
				result = locations[i].room;
			}
			else
			{
				if (pEntityType == PLAYER)
				{
					cout << "The door is locked." << endl;
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

Item* Room::GetItem(string pItem)
{

	Item* result = nullptr;
	int itemIdex = -1;

	for (unsigned int i = 0; i < items.size(); i++) 
	{
		
		if (items.at(i)->GetName() == pItem)
		{
			result = items.at(i);
			itemIdex = i;
		}
	}

	if (itemIdex != -1)
	{
		items.erase(items.begin() + itemIdex);
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

void Room::UseItem(string pItem)
{
	bool usedItem = false;
	for (unsigned int i = 0; i < locations.size(); i++)
	{
		if (locations[i].item != nullptr && locations[i].item->GetName() == pItem)
		{
			locations[i].locked = !locations[i].locked;
			cout << pItem << " was used on " << locations[i].direction << endl;
			usedItem = true;
			break;
		}
	}

	if(!usedItem)
	{
		cout << pItem << " is not useful here." << endl;
	}
}
