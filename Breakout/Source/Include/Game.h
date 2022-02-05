#pragma once

#include "Window.h"

class Game {
public:
	Game();
	void Initialize();
	void Run();
	void Quit();
private:
	void Update(); // All logic is updated in the Game class
private:
	Window mWindow;
	GameState mGameState;
};