#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>

#include "Scene.h"

class Game {
public:
	Game();
	void Run();
	void Quit();
private:
	void Update(); // All logic is updated in the Game class
	void Draw(); // Will be modified when scenes are added
	void Poll(); // Polls events
private:
	GameState mGameState;
	sf::RenderWindow mWindow;
	uint16_t mWindowWidth;
	uint16_t mWindowHeight;

	// The loading screen doesn't have to be a special class
	// The Menu, Gameover, and Level scenes inherit from Scene
	Scene mLoadingScreen, mMenu, mGameOver;
};