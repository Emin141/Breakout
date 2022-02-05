#include "Game.h"
#include <iostream>

int main(int argc, char** argv) {
	Game game;
	game.Initialize();
	game.Run();
	game.Quit();
#ifdef DEBUG
	std::cin.get();
#endif
	return 0;
}