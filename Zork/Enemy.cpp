#include "World.h"
#include "Enemy.h"
#include "Room.h"
#include "Item.h"

Enemy::Enemy()
{
}

Enemy::Enemy(string pName, string pDescription, Room * pActualLocation, World * pWorld, int pHitpoints, int pMaxHit)
{
	name = pName;
	currentLocation = pActualLocation;
	world = pWorld;
	hitpoints = pHitpoints;
	description = pDescription;
	maxHit = pMaxHit;
	entityType = ENEMY;
}

Enemy::~Enemy()
{
}

void Enemy::Go(string pDirection)
{
	Room* newLocation = currentLocation->GoTo(pDirection, entityType, false);

	if (newLocation != nullptr)
	{
		currentLocation = newLocation;
	}
}

void Enemy::Attack(Player * pPlayer)
{
	int damage = Enemy::CalculateDamage();
	pPlayer->TakeDamage(damage);
	cout << "The " << Enemy::GetName() << " attacked you." << endl;
	cout << "Hit: " << damage << " to YOU." << endl << endl;
}

