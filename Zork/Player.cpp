#include "Player.h"
#include "Room.h"
#include "Item.h"

Player::Player()
{
}

Player::Player(string pName, Room* pActualLocation, int pHitpoints, int pMaxHit)
{
	name = pName;
	currentLocation = pActualLocation;
	hitpoints = pHitpoints;
	maxHit = pMaxHit;
	entityType = PLAYER;
}

Player::~Player()
{
}

void Player::Take(string pItem)
{
	Item* item = currentLocation->GetItem(pItem);

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
	currentLocation->UseItem(pItem);
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
		currentLocation->DropItem(item);
		inventory.erase(inventory.begin() + itemIndex);
		cout << item->GetName() << " dropped." << endl;
	}

}

void Player::Look()
{
	currentLocation->TakeALook();
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


