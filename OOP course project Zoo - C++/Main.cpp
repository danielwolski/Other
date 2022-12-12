#include <iostream>
#include <ctime>
#include <conio.h>
#include "World.h"

using namespace std;

#define SIZE 8

int main()
{
	srand(time(NULL));

	char tmpInput;
	World* world;
	while (true) 
	{
			world = new World(SIZE, SIZE);
			world->generate_world();
			break;
	}

	while (world->is_game_over() == false) {
		world->drawWorld();
		world->makeTurn();
	}
	delete world;
	return 0;
}