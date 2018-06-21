#include "World.h"
#include "Npc.h"
#include "Room.h"
#include "Item.h"

Npc::Npc()
{
}

Npc::Npc(string pName, string pDescription, Room * pActualLocation, World * pWorld)
{
	name = pName;
	currentLocation = pActualLocation;
	world = pWorld;
	description = pDescription;
	entityType = NPC;
}

Npc::~Npc()
{
}

void Npc::SetDialogue(map<string, string> pDialogue)
{
	dialogue = pDialogue;
}

void Npc::ProcessDialogue(string words)
{
	bool someValidWord = false;
	vector<string> separatedWords = world->StringToVectorString(words);

	for (unsigned int i = 0; i < separatedWords.size(); i++) 
	{
		try
		{
			string result = dialogue.at(separatedWords[i]);

			cout << result << endl;

			if (separatedWords[i] == "GO") {
				world->WinGame();
			}

			someValidWord = true;
			break;
		}
		catch (exception e)
		{
		}
	}

	if (!someValidWord)
	{
		cout << "I don't understand you, what do you want?" << endl;
	}

}
