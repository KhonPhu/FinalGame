#include <iostream>
#include <SDL.h>
#include "Game.h"


using namespace std;

int main(int argc, char** argv)
{
	Game* game = new Game();

	game->Run((char*)"Welcome", 1000, 800, false);

	Player m_player;
	Enemy m_enemy1;

	
	delete game;
	return 0;

}

