#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "LoadingScreen.h"
#include "Menu.h"

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
	unsigned int mWindowWidth;
	unsigned int mWindowHeight;

	sf::Font mFont;

	LoadingScreen mLoadingScreen;
	Menu mMenu;
	Scene mGameOver;
};