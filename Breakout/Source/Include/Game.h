#pragma once

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "LoadingScreen.h"
#include "Menu.h"
#include "GameOver.h"
#include "Level.h"

class Game {
public:
	Game();
	void run();
	void quit();
private:
	void update();
	void draw();
	void poll();
private:
	// Loading, Menu, GameOver, and Level
	GameState mGameState;

	// Window related stuff
	sf::RenderWindow mWindow;
	sf::Vector2u mWindowSize;

	// Global font, used in all assets
	sf::Font mFont;

	// Mouse condition
	sf::Vector2i mMousePosition;
	bool mLmbWasCliked;

	// Scenes, all inherited from Scene
	LoadingScreen* mLoadingScreen;
	Menu* mMenu;
	GameOver* mGameOver;
	Level* mLevel;

	// GameOver flag
	bool mGameIsOver;

	// DeltaTime device
	sf::Clock mClock;

	// Music 
	// Cairan Tourish - Port Chuilinn / The Cordial Jih / Paddy Taylor's Jig
	sf::Music mBackgroundMusic;

	// Common background for Menu and Game Over screen to be shared 
	sf::Texture mCommonBackground;
};