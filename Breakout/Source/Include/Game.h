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
	~Game();
	void run();
private:
	void update();
	void draw();
	void poll();
private:
	// Loading, Menu, GameOver, and Level enum
	GameState mGameState;

	// Window related stuff
	sf::RenderWindow mWindow;
	sf::Vector2u mWindowSize;

	// Global font, used in all assets
	sf::Font mFont;

	// Mouse condition
	sf::Vector2i mMousePosition;
	bool mLmbWasCliked;

	// Scenes, could be inherited from a single scene, but would
	// make it so that not only the scenes need to be dynamic, but also
	// most objects within them. This is flexible but cumbersome and slow
	std::unique_ptr<LoadingScreen> mLoadingScreen;
	std::unique_ptr<Menu> mMenu;
	std::unique_ptr<GameOver> mGameOver;
	std::unique_ptr<Level> mLevel;

	// GameOver flag
	bool mGameIsOver;

	// DeltaTime device
	sf::Clock mClock;

	// Music 
	// Cairan Tourish - Port Chuilinn / The Cordial Jig / Paddy Taylor's Jig
	sf::Music mBackgroundMusic;

	// Common background for Menu and Game Over screen to be shared 
	sf::Texture mCommonBackground;
};