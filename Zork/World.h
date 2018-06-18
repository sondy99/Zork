#ifndef __World__
#define __World__

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include "Room.h"
#include "Player.h"

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

class World
{
public:
	World();
	~World();
	
	void StartGame();
private:
	vector<string> LocationCommand;
	vector<Room> rooms;
	Player* player;

	bool IsLocationCommand(string command);
	void ManageCommand(string command);
};

#endif //__World__