#include "Player.h"
#include "Room.h"
#include "Item.h"

Player::Player()
{
}

Player::Player(string pName, Room* pActualLocation, int pHitpoints)
{
	name = pName;
	actualLocation = pActualLocation;
	hitpoints = pHitpoints;
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
		Player::IntroduceItemInTheInventory(item);
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
	for (unsigned int i = 0; i < inventory.size(); i++)
	{

		if (inventory.at(i)->GetName() == pItem)
		{
			item = inventory.at(i);
			itemIndex = i;
		}
	}

	if (itemIndex != -1)
	{
		actualLocation->DropItem(item);
		inventory.erase(inventory.begin() + itemIndex);
		cout << item->GetName() << " dropped." << endl;
	}

}

void Player::Look()
{
	actualLocation->TakeALook();
}

void Player::PrintInventory()
{
	if (inventory.size() > 0)
	{
		for (unsigned int i = 0; i < inventory.size(); i++) {
			cout << inventory.at(i)->GetName() << " / " << inventory.at(i)->GetDescription() << endl;
		}
	}
	else 
	{
		cout << "Inventory is empty." << endl;
	}
}


