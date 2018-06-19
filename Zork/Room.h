#ifndef __Room__
#define __Room__

#include "Entity.h"
#include "Item.h"

class Creature;

class Room : public Entity
{
public:
	Room();
	Room(string pName, string pDescription);
	~Room();

	void AddLocation(string pDirection, Room* pRoom);
	void AddLocation(string pDirection, Room* pRoom, bool pLocked, Item* pItem);
	Room* GoTo(string pDirection, EntityType pEntityType);
	Item* GetItem(string pItem);
	vector<Item*> GetItems();
	void AddItem(Item* pItem);
	void DropItem(Item* pItem);
	void UseItem(string pItem);

	struct Location {
		string direction;
		Room* room;
		bool locked = false;
		Item* item = nullptr;
	};

private:
	vector<Location> locations;
	vector<Item*> items;
	vector<Creature*> creatures;
};

#endif //__Room__