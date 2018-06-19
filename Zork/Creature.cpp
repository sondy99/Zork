#include "Creature.h"
#include "Item.h"
#include "Room.h"

Creature::Creature()
{
}

Creature::Creature(string pName, Room* pActualLocation, int pHitpoints, int pMaxHit)
{
	name = pName;
	actualLocation = pActualLocation;
	hitpoints = pHitpoints;
	maxHit = pMaxHit;
}

Creature::Creature(string pName, Room* pActualLocation, int pHitpoints, string pDescription, int pMaxHit)
{
	name = pName;
	actualLocation = pActualLocation;
	hitpoints = pHitpoints;
	description = pDescription;
	maxHit = pMaxHit;
}

Creature::~Creature()
{
}

void Creature::Equip(string pItemName)
{
	Item* item = Creature::GetItemFromInventory(pItemName);

	if (item != nullptr)
	{
		bool equipped = false;

		if (rightHand == nullptr && item->GetItemType() == WEAPON)
		{
			rightHand = item;
			equipped = true;
		}
		else if (leftHand == nullptr && item->GetItemType() == WEAPON)
		{
			leftHand = item;
			equipped = true;
		}
		else if (armor == nullptr && item->GetItemType() == ARMOUR)
		{
			armor = item;
			equipped = true;
		}


		if (equipped)
		{
			cout << item->GetName() + " equipped." << endl;
			Creature::RemoveItemFromInventory(item);
		}
		else
		{
			cout << "You already have an item equipped." << endl;
		}
	}
	else 
	{
		cout << "You don't have that item in the inventory" << endl;
	}

	Creature::ManageStats();
}

void Creature::Unequip(string pItemName)
{
	Item* auxItem = nullptr;
	if (rightHand != nullptr && rightHand->GetName() == pItemName)
	{
		auxItem = rightHand;
		rightHand = nullptr;
	}
	else if (leftHand != nullptr && leftHand->GetName() == pItemName)
	{
		auxItem = leftHand;
		leftHand = nullptr;
	}
	else if (armor != nullptr && armor->GetName() == pItemName)
	{
		auxItem = armor;
		armor = nullptr;
	}

	IntroduceItemInTheInventory(auxItem);

	string message = auxItem != nullptr ? pItemName + " unequipped." : "You don't have that item equipped.";

	cout << message << endl;

	auxItem = nullptr;

	Creature::ManageStats();
}

void Creature::Attack(string pCreatureName)
{
	int damageTaken = actualLocation->Attack(Creature::CalculateDamage(), pCreatureName);

	hitpoints -= damageTaken;

	cout << "Hit: " << damageTaken << " to YOU." << endl;
}

int Creature::CalculateDamage()
{
	return (rand() % (maxHit + 1)) + atk;;
}

void Creature::TakeDamage(int pDamage)
{
	if (Creature::IsAlive())
	{
		hitpoints -= pDamage;
	}
}

Item * Creature::GetItemFromInventory(string pName)
{
	Item* result = nullptr;

	if (inventory.size() > 0)
	{
		for (unsigned int i = 0; i < inventory.size(); i++) {
			if (inventory.at(i)->GetName() == pName)
			{
				result = inventory.at(i);
			}
		}
	}

	return result;
}

void Creature::IntroduceItemInTheInventory(Item * pItem)
{
	if (pItem != nullptr)
	{
		inventory.push_back(pItem);
		cout << pItem->GetName() << " added to the inventory." << endl;
	}
}

void Creature::RemoveItemFromInventory(Item * pItem)
{
	if (inventory.size() > 0)
	{
		int itemIndex = -1;
		for (unsigned int i = 0; i < inventory.size(); i++) {
			if (inventory.at(i)->GetName() == pItem->GetName())
			{
				itemIndex = i;
				break;
			}
		}

		if (itemIndex != -1)
		{
			inventory.erase(inventory.begin() + itemIndex);
		}
	}
}

void Creature::ManageStats()
{
	atk = 0;
	def = 0;

	if (rightHand != nullptr )
	{
		atk += rightHand->GetAtk();
		def += rightHand->GetDef();
	}

	if (leftHand != nullptr)
	{
		atk += leftHand->GetAtk();
		def += leftHand->GetDef();
	}

	if (armor != nullptr)
	{
		def += armor->GetDef();
	}
}

bool Creature::IsAlive()
{
	return hitpoints > 0;
}

void Creature::Stats()
{
	string rightHandMessage = rightHand != nullptr ? rightHand->PrintStats() : "Not item equipped";
	string leftHandMessage = leftHand != nullptr ? leftHand->PrintStats() : "Not item equipped";
	string armorMessage = armor != nullptr ? armor->PrintStats() : "Not item equipped";

	cout << "HP: " << hitpoints << endl;
	cout << "Atk: " << atk << endl;
	cout << "Def: " << def << endl;
	cout << "Armor: " << armorMessage << endl;
	cout << "Right hand: " << rightHandMessage << endl;
	cout << "Left hand: " << leftHandMessage << endl;
}
