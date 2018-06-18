#include "World.h"

using namespace std;

int main() 
{
	World* world = new World();
	
	world->StartGame();

	system("Game Over");
	return 0;
}