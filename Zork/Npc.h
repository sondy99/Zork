#ifndef __Npc__
#define __Npc__


class Worl;
class Room;
class Item;

class Npc : public Creature
{
public:
	Npc();
	Npc(string pName, string pDescription, Room* pActualLocation, World* pWorld);
	~Npc();

	void SetDialogue(map<string, string> pDialogue);
	void ProcessDialogue(string dialogue);

private:
	map<string, string> dialogue;
};

#endif //__Npc__
