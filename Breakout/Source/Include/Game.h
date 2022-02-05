#pragma once

#include "GameState.h"
#include <SDL.h>

#include "Scene.h"

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
	SDL_Surface* mWindowSurface;
	uint16_t mWindowWidth;
	uint16_t mWindowHeight;

	// if the game had more scenes, I would make a map or something
	// however, it really only needs one level scene, and 3 others
	Scene mLoadingScreen, mMenu, mGameOver;
};