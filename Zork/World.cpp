#include "World.h"
#include "Enemy.h"

World::World()
{
	Room* bioTechParking = new Room("Biotechnology lab parking.", "This parking seems to be abandoned, actually everything looks like that, there is only the biotechnology lab where my sister is trapped in the north, an ambulance and my car."); 
	Room* car = new Room("My car.", "Finally, this craziness, it's over, let's go home, mom is waiting for us.", true);
	Room* ambulance = new Room("Ambulance.", "Oh my god! I don't know what I'm going to need, let me take a look and see what can be useful..");
	Room* reception = new Room("Reception.", "There is no one here, I have to find my sister right now, she told me she's stuck in her lab, but which one is it? I can see two hallways and one elevator."); 
	Room* securityRoom = new Room("Security room.", "Jesus! what it's going on here, there are two dead bodies, one of them is a doctor, or what it left of him. There is also a closet.");
	Room* restRoom = new Room("Rest room.", "This is weird where is everyone? where is my sister?.");  
	Room* hallWay = new Room("Hallway.", "Ok! I'm close I have to be careful, I don't know what I can found here. There are two labs in here, the lab A to the east  and the lab B to the west.");
	Room* labA = new Room("Lab A.", "This is the biggest, fancy lab I've ever seen before."); 
	Room* labB = new Room("Lab B.", "Crap, there was a massacre here!"); 

	//weapons and armor
	Item* vest = new Item("VEST", "This vest could be useful to have some protection here.", ARMOUR, 0, 2);
	Item* tube = new Item("TUBE", "Haha! I like this tube, I can smash whoever wants to hurt my sister..", WEAPON, 4, 1);
	Item* scalpel = new Item("SCALPEL", "Oh, this scalpel, it's really sharp.", WEAPON, 5, 0);

	//common items
	Item* rock = new Item("ROCK", "A rock it's cover by leaves");
	Item* key = new Item("KEY", "Yeah! I found the key.");

	Item* mapOnTheWall = new Item("MAP", "That map could be interesting.");
	mapOnTheWall->SetPosibleToTake(false);
	mapOnTheWall->SetNote("Ok, in the north of the Reception is the hallway and there are two labs, lab A to the east and lab B to the west.");

	Item* deadDoctor = new Item("DOCTOR", "It is the weird doctor, I bet all of this is his foul, Caroline told me he was doing some dangerous experiments.");
	deadDoctor->SetPosibleToTake(false);
	deadDoctor->PutItemInside(key);

	Item* closet = new Item("CLOSET", "This closet has to contain something useful.", CONTAINER);
	closet->SetPosibleToTake(false);
	closet->PutItemInside(vest);

	Item* computer = new Item("COMPUTER", "I really like that computer!",READABLE);
	computer->SetPosibleToTake(false);
	computer->SetNote("Where is she??? where is she?? Yeaaaah! I found her, my sister is in the lab A.");

	bioTechParking->AddLocation(NORTH, reception);
	bioTechParking->AddLocation(EAST, ambulance, true, rock);
	bioTechParking->AddLocation(SOUTH, car, true, "You can't go without your sister");

	car->AddLocation(NORTH, bioTechParking);

	ambulance->AddLocation(WEST, bioTechParking);

	reception->AddLocation(SOUTH, bioTechParking);
	reception->AddLocation(NORTH, hallWay);
	reception->AddLocation(EAST, securityRoom);
	reception->AddLocation(WEST, restRoom);

	securityRoom->AddLocation(WEST, reception);

	restRoom->AddLocation(EAST, reception);

	hallWay->AddLocation(SOUTH, reception);
	hallWay->AddLocation(EAST, labA, true, key);
	hallWay->AddLocation(WEST, labB);

	labA->AddLocation(WEST, hallWay);

	labB->AddLocation(EAST, hallWay);

	bioTechParking->AddItem(rock);
	ambulance->AddItem(scalpel);
	reception->AddItem(computer);
	securityRoom->AddItem(deadDoctor);
	securityRoom->AddItem(closet);
	restRoom->AddItem(mapOnTheWall);
	restRoom->AddItem(tube);
	
	player = new Player("Daniel","The inmortal", bioTechParking, this, 35, 4);

	Enemy* rat = new Enemy("RAT", "What is that... it's an infected rat?", restRoom, this, 15, 3);
	Enemy* zombie = new Enemy("DOCTOR", "WTF! what is this!? doctor are you ok?", labB, this, 40, 8);

	creatures.push_back(rat);
	creatures.push_back(zombie);

	Npc* sister = new Npc("SISTER", "Finally, I found you!! fast go with me, we have to leave, the car is outside waiting for us..", labA, this);

	map<string, string> dialogue;
	dialogue.insert(pair<string, string>("HI", "Finally you are here."));
	dialogue.insert(pair<string, string>("GO", "Ok, perfect let's go."));
	sister->SetDialogue(dialogue);

	npcs.push_back(sister);

	player->Look(true);
	cout << endl;

	LocationCommand.push_back(NORTH);
	LocationCommand.push_back(SOUTH);
	LocationCommand.push_back(WEST);
	LocationCommand.push_back(EAST);

	World::RecurrentEvents([&] {World::Event(); }, 1000);
}

World::~World()
{
}

vector<Enemy*> World::GetEnemies()
{
	return creatures;
}

Enemy* World::GetEnemy(string pEnemyName)
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

vector<Npc*> World::GetNpcs()
{
	return npcs;
}

Npc* World::GetNpc(string pNpcName)
{
	Npc* resutl = nullptr;

	if (npcs.size() > 0)
	{
		for (unsigned int i = 0; i < npcs.size(); i++)
		{
			if (npcs.at(i)->GetName() == pNpcName)
			{
				resutl = npcs.at(i);
			}
		}
	}

	return resutl;
}

void World::RemoveNpc(string pNpcName)
{
	if (npcs.size() > 0)
	{
		int indexNpc = -1;
		for (unsigned int i = 0; i < npcs.size(); i++)
		{
			if (npcs.at(i)->GetName() == pNpcName)
			{
				indexNpc = i;
			}
		}

		if (indexNpc != -1)
		{
			npcs.erase(npcs.begin() + indexNpc);
		}
	}
}

void World::StartGame()
{
	while (!gameOver)
	{
		string commandByUser;

		getline(cin, commandByUser);
		
		transform(commandByUser.begin(), commandByUser.end(), commandByUser.begin(), ::toupper);

		if (!gameOver)
		{
			if (player->IsAlive())
			{

				cout << endl;
				if (!isInConversation)
				{
					ManageCommand(commandByUser);
				}
				else
				{
					World::ProcessConversation(commandByUser);
				}
				cout << endl;
			}
			else
			{
				commandByUser = EXIT_GAME;
				cout << "You are dead." << endl;
			}

			if (commandByUser == EXIT_GAME)
			{
				gameOver = true;
			}
		}
	}
}

void World::PrintHelp()
{
	cout << "This is the list of commands and how to use them (The command could be use on upper or lower case):" << endl;
	cout << "NORTH/SOUTH/EAST/WEST -> To navigate through the world." << endl;
	cout << "INVENTORY -> Show you your current inventory." << endl;
	cout << "STATS -> Show you your stats (HP, Atk, Def, weapons, armor)." << endl;
	cout << "LOOK -> Take a look at the current location." << endl;
	cout << "EXIT_GAME -> Equit from the game." << endl;
	cout << "TIME -> Print the seconds in the game." << endl;
	cout << "TAKE <item name> -> Take an item from the room." << endl;
	cout << "USER <item name> <direction> (NORTH/SOUTH/EAST/WEST) > -> Open closed gates." << endl;
	cout << "DROP <item name> -> Drop items from your inventory." << endl;
	cout << "EQUIP <item name> -> Equip items from your inventory, you can have two weapons and one armor." << endl;
	cout << "UNEQUIP <item name> -> unique items from you." << endl;
	cout << "READ <item> -> Read items if there are readable." << endl;
	cout << "OPEN <item> -> Open items and take the items inside if the item is a container." << endl;
	cout << "LOOT <item> -> LOOT items and take the items inside if the item is a container." << endl;
	cout << "HI <npcName> -> Starts a conversation with an NPC." << endl;
	cout << "BYE -> Ends a conversation with an NPC." << endl;
	cout << "GO -> Tells your sister to go and she is going with you." << endl;

}

void World::ManageCommand(string command)
{
	vector<string> separatedCommands = World::StringToVectorString(command);

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
			else if (separatedCommands[0] == HELP)
			{
				World::PrintHelp();
			}
			else
			{
				cout << "Unknown command." << endl;
			}
			break;
		}
		case 2:
		{
			if (separatedCommands[0] == TAKE)
			{
				player->Take(separatedCommands[1]);
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
			else if (separatedCommands[0] == OPEN || separatedCommands[0] == LOOT)
			{
				player->Open(separatedCommands[1]);
			}
			else if (separatedCommands[0] == HI)
			{
				World::StartConversation(separatedCommands[1]);
				World::ProcessConversation(command);
			}
			else
			{
				cout << "Unknown command." << endl;
			}
			break;
		}
		case 3:
		{
			if (separatedCommands[0] == USE)
			{
				player->Use(separatedCommands[1], separatedCommands[2]);
			}
			break;
		}
		default:
		{
			cout << "Unknown command." << endl;
			break;
		}
	}

}

void World::ProcessConversation(string words)
{
	if (npcInConversation != nullptr) {
		vector<string> separatedWords = World::StringToVectorString(words);


		if (separatedWords.size() == 1)
		{
			if (separatedWords[0] == BYE)
			{
				npcInConversation = nullptr;
				isInConversation = false;
			}
		}

		npcInConversation->ProcessDialogue(words);
	}
}

void World::StartConversation(string pNpcName)
{
	npcInConversation = World::GetNpc(pNpcName);

	if (npcInConversation != nullptr && npcInConversation->GetCurrenLocation()->GetName() == player->GetCurrenLocation()->GetName())
	{
		isInConversation = true;
	}

}


vector<string> World::StringToVectorString(string words)
{
	string buf;
	stringstream ss(words);

	vector<string> separatedCommands;

	while (ss >> buf)
		separatedCommands.push_back(buf);

	return separatedCommands;
}


void World::WinGame()
{
	RemoveNpc(npcInConversation->GetName());
	npcInConversation = nullptr;
	isInConversation = false;
	player->SetWin(true);
}

void World::GameOver()
{
	gameOver = true;
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
		if (creatures.size() != 0)
		{
			Enemy* creatureRandom = creatures[(rand() % (creatures.size()))];

			//Move creature random to a location random
			creatureRandom->Go(LocationCommand[(rand() % (LocationCommand.size()))]);

			//Creature attack randomly to the player
			if (creatureRandom->GetCurrenLocation()->GetName() == player->GetCurrenLocation()->GetName())
			{
				if (rand() % 2 == 1)
				{
					if (player->IsAlive()) {
						creatureRandom->Attack(player);
					}
				}
			}
		}
	}

}