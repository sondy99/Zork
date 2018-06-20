#ifndef __Enemy__
#define __Enemy__


class Worl;
class Room;
class Item;

class Enemy : public Creature
{
public:
	Enemy();
	Enemy(string pName, string pDescription, Room* pActualLocation, World* pWorld, int pHitpoints, int pMaxHit = 1);
	~Enemy();

	void Go(string pDirection);
	void Attack(Player* pPlayer);

private:

};

#endif //__Enemy__
