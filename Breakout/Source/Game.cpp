#include "Game.h"

#include <iostream>

#include "LoadingScreen.h"
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"

Game::Game() {
	// Logger
	plog::init(plog::debug, "Error.log");

	// Constructor call
	mGameState = GameState::LOADING;
	mMousePosition = sf::Mouse::getPosition();
	mLmbWasCliked = false;

	// OpenGL context settings, for modern OpenGL at least 3.3
	sf::ContextSettings ContextSettings;
	ContextSettings.antialiasingLevel = 4;
	ContextSettings.majorVersion = 3;
	ContextSettings.minorVersion = 3;

	// Gets the biggest possible video mode
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

	mWindow.create(
		videoMode,
		"Breakout",
		sf::Style::Fullscreen,
		ContextSettings
	);
	mWindowSize = mWindow.getSize();
	mWindow.setFramerateLimit(60);

	try {
		if (!mFont.loadFromFile("Resource/Fonts/Biolinum.ttf"))
			throw "Cannot load font at Resource/Fonts/Biolinum.tff";
	}
	catch (std::string message) {
		PLOGD << message;
		exit(1);
	}

	// Loading screen until the game is loaded
	mLoadingScreen = new LoadingScreen();
	mLoadingScreen->load(mFont, { mWindowSize.x / 2.0f, mWindowSize.y / 2.0f });
	mWindow.clear(sf::Color::Black);
	mLoadingScreen->draw(mWindow);
	mWindow.display();

	// Menu screen
	mMenu = new Menu();
	mMenu->load(mFont, sf::Vector2f(mWindowSize.x, mWindowSize.y));

	// Game over screen
	mGameOver = new GameOver();
	mGameOver->load(mFont, sf::Vector2f(mWindowSize.x, mWindowSize.y));

	mGameState = GameState::MENU;
	mLevel = new Level();
	mGameIsOver = false;
}

void Game::run() {
	while (mGameState != GameState::QUIT) {
		update();
		draw();
		poll();
	}
}

void Game::quit() {
	mWindow.close();
	delete mLoadingScreen;
	delete mMenu;
	delete mGameOver;
	delete mLevel;
	// Everything else is RAII managed to deallocate
}

void Game::update() {
	// Checks collision, HP, Score, Player lives, increases ball speed
	// adding and removing of actors, menu choices etc.
	mMousePosition = sf::Mouse::getPosition();
	float deltaTime = mClock.restart().asSeconds();

	switch (mGameState) {

		// If on menu
	case GameState::MENU:
		mWindow.setMouseCursorVisible(true);
		if (mLmbWasCliked) {
			switch (mMenu->getMenuChoice(mMousePosition)) {
			case MenuChoice::EXIT:
				mGameState = GameState::QUIT;
				break;
			case MenuChoice::LEVEL_1:
				mGameState = GameState::LEVEL;
				mLevel->loadFromXML("Resource/Levels/Level1.xml", mWindow);
				break;
			case MenuChoice::LEVEL_2:
				mGameState = GameState::LEVEL;
				mLevel->loadFromXML("Resource/Levels/Level2.xml", mWindow);
				break;
			case MenuChoice::LEVEL_3:
				mGameState = GameState::LEVEL;
				mLevel->loadFromXML("Resource/Levels/Level3.xml", mWindow);
				break;
			case MenuChoice::NONE:
			default:
				break;
			}
			mLmbWasCliked = false;
		}
		break;

		// If a level is loaded
	case GameState::LEVEL:
		mWindow.setMouseCursorVisible(false);
		mLevel->update(mMousePosition, mWindow, deltaTime, mGameIsOver);
		if (mGameIsOver) {
			mGameState = GameState::GAMEOVER;
			mGameIsOver = false;

		}
		break;

		// If the game over screen is displayed
	case GameState::GAMEOVER:
		mWindow.setMouseCursorVisible(true);
		if (mLmbWasCliked) {
			switch (mGameOver->getMenuChoice(mMousePosition))
			{
			case GameOverChoice::BACK_TO_MENU:
				mGameState = GameState::MENU;
				mLmbWasCliked = false;
				break;
			case GameOverChoice::EXIT:
				mGameState = GameState::QUIT;
				break;
			default:
				break;
			}
		}
		break;

	default:
		break;
	}


}

void Game::draw() {
	// Clear
	mWindow.clear(sf::Color::Black);

	// Chooses correct scene to draw
	// If the scenes were pretty heavy, this would be a bad idea
	// since all the assets are loaded at all times like this
	// However, since the game is light, and the only 3 scenes other than 
	// the chosen level are the loading screen (literally just text),
	// a menu (barely any resources used), and a game over screen 
	// (even less resources used), this is completely fine. 
	switch (mGameState) {
	case GameState::LOADING:
		mLoadingScreen->draw(mWindow);
		break;
	case GameState::MENU:
		mMenu->draw(mWindow);
		break;
	case GameState::LEVEL:
		mLevel->draw(mWindow);
		break;
	case GameState::GAMEOVER:
		mGameOver->updatePlayerScore(mLevel->getPlayerScore());
		mGameOver->draw(mWindow);
		break;
	default:
		break;
	}

	// Swaps the back buffer
	mWindow.display();
}

void Game::poll() {
	sf::Event mEvent;

	while (mWindow.pollEvent(mEvent)) {
		switch (mEvent.type) {
		case sf::Event::Closed:
			mGameState = GameState::QUIT;
			break;
		case sf::Event::KeyPressed:
			switch (mEvent.key.code) {
			case sf::Keyboard::Escape:
			case sf::Keyboard::Q:
				mGameState = GameState::QUIT;
				break;
			default:
				break;
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (mEvent.mouseButton.button == sf::Mouse::Left)
				mLmbWasCliked = true;
			break;
		default:
			break;
		}
	}
}