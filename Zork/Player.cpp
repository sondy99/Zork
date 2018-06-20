#include "World.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Enemy.h"

Player::Player()
{
}

Player::Player(string pName, string pDescription, Room * pActualLocation, World * pWorld, int pHitpoints, int pMaxHit)
{
	name = pName;
	currentLocation = pActualLocation;
	world = pWorld;
	hitpoints = pHitpoints;
	maxHit = pMaxHit;
	entityType = PLAYER;
}

Player::~Player()
{
}

void Player::Go(string pDirection)
{
	Room* newLocation = currentLocation->GoTo(pDirection, entityType);

	if (newLocation != nullptr)
	{
		currentLocation = newLocation;
		Player::Look(false);
	}
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

void Player::Look(bool pByCommand)
{
	cout << currentLocation->GetName() << endl;

	if (!currentLocation->IsAlreadyBeenHere() || pByCommand)
	{
		cout << currentLocation->GetDescription(pByCommand) << endl;
	}

	vector<Enemy*> creatures = world->GetEnemies();
	if (creatures.size() > 0)
	{
		for (unsigned int i = 0; i < creatures.size(); i++) {
			if (creatures.at(i)->GetCurrenLocation()->GetName() == currentLocation->GetName())
			{
				cout << creatures.at(i)->GetDescription() << endl;
			}
		}
	}

	vector<Item*> items = currentLocation->GetItems();
	if (items.size() > 0)
	{
		for (unsigned int i = 0; i < items.size(); i++) {
			cout << items.at(i)->GetDescription() << endl;
		}
	}
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

void Player::Attack(string pCreatureName)
{
	Enemy* target = world->GetEnemy(pCreatureName);

	if (target != nullptr)
	{
		int damage = Player::CalculateDamage();
		target->TakeDamage(damage);

		cout << "Hit: " << damage << " to " << pCreatureName << "." << endl;

		if (!target->IsAlive())
		{
			cout << target->GetName() << " is dead." << endl;
			world->RemoveCreature(target->GetName());
		}
		else
		{
			int returnDamage = target->CalculateDamage() - def;
			hitpoints -= returnDamage;
			cout << "Hit: " << returnDamage << " to YOU." << endl;
		}
	}
	else
	{
		cout << "There is no creature like that." << endl;
	}
}

