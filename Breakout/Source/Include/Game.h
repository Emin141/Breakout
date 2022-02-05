#pragma once

#include "GameState.h"
#include <SDL.h>

class Game {
public:
	Game();
	void Initialize();
	void Run();
	void Quit();
private:
	void Update(); // All logic is updated in the Game class
	void Draw(); // Will be modified when scenes are added
private:
	GameState mGameState;
	SDL_Window* mWindowPtr;
	uint16_t mWindowWidth;
	uint16_t mWindowHeight;
};