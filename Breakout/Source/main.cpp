#include "Game.h"
#include <iostream>

int main(int argc, char** argv) {
	Game game;
	game.Initialize();
	game.Run();
	game.Quit();
	return 0;
}