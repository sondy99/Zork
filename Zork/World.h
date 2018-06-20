#ifndef __World__
#define __World__

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include "Room.h"
#include "Player.h"

class Enemy;

using namespace std;

static const string HELP = "HELP";
static const string NORTH = "NORTH";
static const string SOUTH = "SOUTH";
static const string WEST = "WEST";
static const string EAST = "EAST";
static const string UP = "UP";
static const string DOWN = "DOWN";
static const string INVENTORY = "INVENTORY";
static const string LOOK = "LOOK";
static const string TAKE = "TAKE";
static const string USE = "USE";
static const string DROP = "DROP";
static const string EQUIP = "EQUIP";
static const string UNEQUIP = "UNEQUIP";
static const string STATS = "STATS";
static const string ATTACK = "ATTACK";
static const string EXIT_GAME = "EXIT";
static const string TIME = "TIME";
static const string READ = "READ";
static const string OPEN = "OPEN";
static const string LOOT = "LOOT";

class World
{
public:
	World();
	~World();

	vector<Enemy*> GetEnemies();
	Enemy* GetEnemy(string pEnemyName);
	void RemoveCreature(string pCreatureName);
	void StartGame();
private:
	vector<string> LocationCommand;
	vector<Enemy*> creatures;
	Player* player;
	int sec = 0;

	bool IsLocationCommand(string command);
	void ManageCommand(string command);
	void RecurrentEvents(function<void(void)> func, unsigned int interval);
	void Event();
};

#endif //__World__