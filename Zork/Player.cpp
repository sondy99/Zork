#include "Player.h"
#include "Room.h"
#include "Item.h"

Player::Player()
{
}

Player::Player(string pName, Room* pActualLocation)
{
	name = pName;
	actualLocation = pActualLocation;
}

Player::~Player()
{
}

void Player::Go(string pDirection)
{
	Room* posibleLocation = actualLocation->GoTo(pDirection);

	if (posibleLocation != nullptr)
	{
		actualLocation = posibleLocation;
		actualLocation->TakeALook();
	}
}

void Player::Take(string pItem)
{
	Item* item = actualLocation->GetItem(pItem);

	if (item != nullptr)
	{
		inventroy.push_back(item);
		cout << item->GetName() << " added to the inventory." << endl;
	}
	else {
		cout << "There is not item named like that." << endl;
	}
}

void Player::Use(string pItem)
{
	actualLocation->UseItem(pItem);
}

void Player::Drop(string pItem)
{
	Item* item = nullptr;
	int itemIndex = -1;
	for (unsigned int i = 0; i < inventroy.size(); i++)
	{

		if (inventroy.at(i)->GetName() == pItem)
		{
			item = inventroy.at(i);
			itemIndex = i;
		}
	}

	if (itemIndex != -1)
	{
		actualLocation->DropItem(item);
		inventroy.erase(inventroy.begin() + itemIndex);
		cout << item->GetName() << " dropped." << endl;
	}

}

void Player::Look()
{
	actualLocation->TakeALook();
}

void Player::PrintInventory()
{
	if (inventroy.size() > 0)
	{
		for (unsigned int i = 0; i < inventroy.size(); i++) {
			cout << inventroy.at(i)->GetName() << " / " << inventroy.at(i)->GetDescription() << endl;
		}
	}
	else 
	{
		cout << "Inventory is empty." << endl;
	}
}


