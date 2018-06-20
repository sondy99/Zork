#include "World.h"
#include "Enemy.h"

World::World()
{
	Room* bioTechParking = new Room("Biotechnology lab parking.", "This parking seems to be abandoned, actually every looks like that, there is only the biotechnology lab where my sister is trapped in the north, an ambulance and my car."); //piedra para abrir la ambulancia
	Room* car = new Room("My car.", "Finally, this craziness, it's over, let's go home, mom is waiting for us.");
	Room* ambulance = new Room("Ambulance.", "Oh my god! I don't know what I'm going to need, let me take a look and see what can be useful.."); //bisturi (arma)
	Room* reception = new Room("Reception.", "There's no one here, I have to find my sister right now, she told me she's stuck in her lab, but which one is it? I can see two hallways and one elevator."); //computadora para ser leida donde esta mi hermana
	Room* securityRoom = new Room("Security room.", "Jesus! what it's going on here, there are two dead bodies, one of them is a doctor, or what it left of him. There is also a closet.");// llave dentro del doctor, y chaleco en el closet
	Room* restRoom = new Room("Rest room.", "It's weird where is everyone? where is my sister?.");  //map y un tubo
	Room* hallWay = new Room("Hallway.", "Ok! I'm close I have to be careful, I don't know what I can found here. There are two labs in here, the lab A to the east  and the lab B to the west.");
	Room* labA = new Room("Lab A.", "This is the biggest fancy lab I've ever seen before."); //Hermana
	Room* labB = new Room("Lab B.", "Crap, there was a massacre here!"); //zoombi cabilla

	//weapons and armor
	Item* vest = new Item("VEST", "This vest could be useful to have some protection here.", ARMOUR, 0, 2);
	Item* tube = new Item("TUBE", "Haha! I like this tune, I can smash whoever wants to hurt my sister..", WEAPON, 4, 1);
	Item* scalpel = new Item("SCALPEL", "Oh, this scalpel, it's really sharp.", WEAPON, 5, 0);

	//common items
	Item* map = new Item("MAP", "That the maps could interesting.");
	Item* rock = new Item("ROCK", "A rock it's cover by leaves");
	Item* key = new Item("KEY", "Yeah! I found the key.");
	Item* closet = new Item("CLOSET", "This closet has to contain something useful.", CONTAINER);
	closet->SetPosibleToTake(false);
	closet->PutItemInside(vest);

	Item* computer = new Item("COMPUTER", "I really like that computer!",READABLE);
	computer->SetPosibleToTake(false);
	computer->SetNote("Where is it??? where is it?? Yeaaaah! I found it, my sister is in the lab A.");

	bioTechParking->AddLocation(NORTH, reception);
	bioTechParking->AddLocation(EAST, ambulance, true, rock);
	bioTechParking->AddLocation(SOUTH, car); //sister finish

	car->AddLocation(NORTH, bioTechParking);

	ambulance->AddLocation(WEST, bioTechParking);

	reception->AddLocation(NORTH, hallWay);
	reception->AddLocation(EAST, securityRoom);
	reception->AddLocation(WEST, restRoom);

	hallWay->AddLocation(EAST, labA, true, key);
	hallWay->AddLocation(EAST, labB, true, key);

	bioTechParking->AddItem(rock);
	ambulance->AddItem(scalpel);
	reception->AddItem(computer);
	securityRoom->AddItem(key);
	securityRoom->AddItem(closet);
	restRoom->AddItem(map);
	restRoom->AddItem(tube);
	
	player = new Player("Daniel","The inmortal", bioTechParking, this, 35, 8);

	Enemy* rat = new Enemy("RAT", "What is that... it's a infected rat?", restRoom, this, 10, 4);
	Enemy* zombie = new Enemy("ZOMBIE", "WTF! what is this!? doctor are you ok? ohhh nooo!! stop!", labB, this, 25, 6);

	creatures.push_back(rat);
	creatures.push_back(zombie);

	player->Look(true);
	cout << endl;

	LocationCommand.push_back(NORTH);
	LocationCommand.push_back(SOUTH);
	LocationCommand.push_back(WEST);
	LocationCommand.push_back(EAST);
	LocationCommand.push_back(UP);
	LocationCommand.push_back(DOWN);

	World::RecurrentEvents([&] {World::Event(); }, 1000);
}

World::~World()
{
}

vector<Enemy*> World::GetEnemies()
{
	return creatures;
}

Enemy * World::GetEnemy(string pEnemyName)
{
	Enemy* resutl = nullptr;

	if (creatures.size() > 0)
	{
		for (unsigned int i = 0; i < creatures.size(); i++)
		{
			if (creatures.at(i)->GetName() == pEnemyName)
			{
				resutl = creatures.at(i);
			}
		}
	}

	return resutl;
}

void World::RemoveCreature(string pCreatureName)
{
	if (creatures.size() > 0)
	{
		int indexCreature = -1;
		for (unsigned int i = 0; i < creatures.size(); i++)
		{
			if (creatures.at(i)->GetName() == pCreatureName)
			{
				indexCreature = i;
			}
		}

		if (indexCreature != -1)
		{
			creatures.erase(creatures.begin() + indexCreature);
		}
	}
}

void World::StartGame()
{
	bool gameOver = false;
	while (!gameOver)
	{
		string commandByUser;

		getline(cin, commandByUser);

		transform(commandByUser.begin(), commandByUser.end(), commandByUser.begin(), ::toupper);

		if (player->IsAlive())
		{
			ManageCommand(commandByUser);
			cout << endl;
		}
		else
		{
			commandByUser = EXIT_GAME;
			cout << "You are dead." << endl;
		}

		if (commandByUser == EXIT_GAME)
		{
			//todo Imprimir stats de game over
			gameOver = true;
		}
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
				player->Look(true);
			}
			else if (separatedCommands[0] == STATS)
			{
				player->Stats();
			}
			else if (separatedCommands[0] == TIME)
			{
				cout << "Time:" << sec << " sec." << endl;
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
			else if (separatedCommands[0] == EQUIP)
			{
				player->Equip(separatedCommands[1]);
			}
			else if (separatedCommands[0] == UNEQUIP)
			{
				player->Unequip(separatedCommands[1]);
			}
			else if (separatedCommands[0] == ATTACK)
			{
				player->Attack(separatedCommands[1]);
			}
			else if (separatedCommands[0] == READ)
			{
				player->Read(separatedCommands[1]);
			}
			else if (separatedCommands[0] == OPEN)
			{
				player->Open(separatedCommands[1]);
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

void World::RecurrentEvents(function<void(void)> event, unsigned int interval)
{
	std::thread([event, interval]() {
		while (true)
		{
			event();
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
		}
	}).detach();
}

void World::Event() 
{
	sec++;

	if (sec % 5 == 0) {
		Enemy* creatureRandom = creatures[(rand() % (creatures.size()))];

		//Move creature random to a location random
		creatureRandom->Go(LocationCommand[(rand() % (LocationCommand.size()))]);

		//Creature attack randomly to the player
		if (creatureRandom->GetCurrenLocation()->GetName() == player->GetCurrenLocation()->GetName()) 
		{
			if (rand() % 2 == 1) 
			{
				creatureRandom->Attack(player);
			}
		}
	}

}