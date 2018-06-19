#include "World.h"

using namespace std;

int main() 
{
	World* world = new World();
	
	world->StartGame();

	cout << "Game Over." << endl;

	cin.get();
	return 0;
}