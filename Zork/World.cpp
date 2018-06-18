#include "World.h"
World::World()
{
	Room* roomUno = new Room("roomUno", "habitacion 1 norte o sur");
	Room* roomDos = new Room("roomDos", "habitacion 2 west o south");
	Room* roomTres = new Room("roomTres", "habitacion 3 norte o este");
	Room* roomCuatro = new Room("roomCuatro", "habitacion 4 este");
	Room* roomCinco = new Room("roomCinco", "habitacion 5 oeste");

	Item* key = new Item("KEY", "This key seems to open a specific door.");
	Item* card = new Item("CARD", "This key seems to open a specific door.");
	Item* rock = new Item("ROCK", "Simple rock.");
	Item* ball = new Item("BALL", "Simple big rock.");
	Item* rose = new Item("ROSE", "Simple rose.");

	roomUno->AddLocation(NORTH, roomDos, true, key);
	roomUno->AddLocation(SOUTH, roomTres);

	roomDos->AddLocation(SOUTH, roomUno);
	roomDos->AddLocation(WEST, roomCuatro);

	roomTres->AddLocation(NORTH, roomUno);
	roomTres->AddLocation(EAST, roomCinco);

	roomCuatro->AddLocation(EAST, roomDos);

	roomCinco->AddLocation(WEST, roomTres);

	roomTres->AddItem(key);
	roomTres->AddItem(card);
	roomTres->AddItem(rock);

	
	roomDos->AddItem(ball);

	roomUno->AddItem(rose);


	player = new Player("Sondy", roomUno);

	LocationCommand.push_back(NORTH);
	LocationCommand.push_back(SOUTH);
	LocationCommand.push_back(WEST);
	LocationCommand.push_back(EAST);
	LocationCommand.push_back(UP);
	LocationCommand.push_back(DOWN);

	roomUno->TakeALook();
}

World::~World()
{
}

void World::StartGame()
{
	bool gameOver = false;
	while (!gameOver)
	{
		string commandByUser;

		getline(cin, commandByUser);

		transform(commandByUser.begin(), commandByUser.end(), commandByUser.begin(), ::toupper);

		ManageCommand(commandByUser);

		gameOver = commandByUser == "exit";
	}
}

void World::ManageCommand(string command)
{
	string buf;
	stringstream ss(command);

	vector<string> separatedCommands;

	while (ss >> buf)
		separatedCommands.push_back(buf);

	switch (separatedCommands.size())
	{
		case 1:
		{
			if (separatedCommands[0] == INVENTORY)
			{
				player->PrintInventory();
			}
			else if (IsLocationCommand(separatedCommands[0]))
			{
				player->Go(separatedCommands[0]);
			}
			else if (separatedCommands[0] == LOOK)
			{
				player->Look();
			}
			else
			{
				cout << "Command unknown" << endl;
			}
			break;
		}
		case 2:
		{
			if (separatedCommands[0] == TAKE)
			{
				player->Take(separatedCommands[1]);
			}
			else if (separatedCommands[0] == USE)
			{
				player->Use(separatedCommands[1]);
			}
			else if (separatedCommands[0] == DROP)
			{
				player->Drop(separatedCommands[1]);
			}
			else
			{
				cout << "Command unknown" << endl;
			}
			break;
		}
		default:
		{
			cout << "Command unknown" << endl;
			break;
		}
	}

}

bool World::IsLocationCommand(string command)
{
	bool result = false;

	for (unsigned int i = 0; i < LocationCommand.size(); i++) {
		if (LocationCommand[i] == command) {
			result = true;
			break;
		}
	}

	return result;
}