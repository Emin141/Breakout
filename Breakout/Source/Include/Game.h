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
	void Draw(); // Chooses the scene to draw and draws it
	void Poll(); // Polls events
private:
	// Loading, Menu, GameOver, and Level
	GameState mGameState;

	// Window related stuff
	sf::RenderWindow mWindow;
	unsigned int mWindowWidth;
	unsigned int mWindowHeight;

	// Global font, used in all assets
	sf::Font mFont;

	// Mouse condition
	sf::Vector2i mMousePosition;
	bool mLmbWasCliked;

	// Scenes, all inherited from Scene
	LoadingScreen mLoadingScreen;
	Menu mMenu;
	Scene mGameOver;
};