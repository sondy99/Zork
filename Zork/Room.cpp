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

void Room::AddItem(Item* pItem)
{
	items.push_back(pItem);
}

void Room::AddCreature(Creature * pCreature)
{
	creatures.push_back(pCreature);
}

void Room::RemoveCreature(string pCreatureName)
{
	if (creatures.size() > 0)
	{
		int indexCreature = -1;
		for (unsigned int i = 0; i < creatures.size(); i++)
		{
			if (creatures.at(i)->GetName() == pCreatureName)
			{
				indexCreature = i;
			}
		}

		if (indexCreature != -1)
		{
			creatures.erase(creatures.begin() + indexCreature);
		}
	}
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

void Room::TakeALook()
{
	cout << GetName() << endl;
	cout << GetDescription() << endl;

	if (creatures.size() > 0)
	{
		for (unsigned int i = 0; i < creatures.size(); i++) {
			cout << creatures.at(i)->GetDescription() << endl;
		}
	}

	if (items.size() > 0)
	{
		for (unsigned int i = 0; i < items.size(); i++) {
			cout << items.at(i)->GetDescription() << endl;
		}
	}
}

Creature* Room::GetCreature(string pCreatureName)
{
	Creature* resutl = nullptr;

	if (creatures.size() > 0)
	{
		for (unsigned int i = 0; i < creatures.size(); i++)
		{
			if (creatures.at(i)->GetName() == pCreatureName)
			{
				resutl = creatures.at(i);
			}
		}
	}

	return resutl;
}
