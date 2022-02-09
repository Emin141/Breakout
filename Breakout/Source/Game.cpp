#include "Game.h"

#include <iostream>
#include "LoadingScreen.h"

Game::Game() {
	// Constructor call
	mGameState = GameState::LOADING;
	mMousePosition = sf::Mouse::getPosition();
	mLmbWasCliked = false;
	mPlayerScore = 0;

	sf::ContextSettings ContextSettings;
	ContextSettings.antialiasingLevel = 4;
	ContextSettings.majorVersion = 3;
	ContextSettings.minorVersion = 3;

	mWindow.create(
		sf::VideoMode(1024, 720),
		"Breakout",
		sf::Style::Fullscreen,
		ContextSettings
	);
	mWindowSize = mWindow.getSize();
	mWindow.setFramerateLimit(60);

	mFont.loadFromFile("Resource/Fonts/Helvetica.ttf");

	// Loading screen until the game is loaded
	mLoadingScreen.Load(mFont, 
		{ mWindowSize.x / 2.0f, mWindowSize.y / 2.0f });
	mWindow.clear(sf::Color::Black);
	mLoadingScreen.Draw(mWindow);
	mWindow.display();

	// Menu screen
	mMenu.Load(mFont, sf::Vector2f(mWindowSize.x, mWindowSize.y));

	// Game over screen
	mGameOver.Load(mFont, sf::Vector2f(mWindowSize.x, mWindowSize.y));

	//sf::sleep(sf::seconds(1));

	mGameState = GameState::MENU;
}

void Game::Run() {
	while (mGameState!=GameState::QUIT) {
		Update();
		Draw();
		Poll();
	}
}

void Game::Quit() {
	mWindow.close();
	// Everything else is RAII managed to deallocate
}

void Game::Update() {
	// Checks collision, HP, Score, Player lives, increases ball speed
	// adding and removing of actors, menu choices etc.
	mMousePosition = sf::Mouse::getPosition();
	sf::Time deltaTime = mClock.restart();
	float dt = deltaTime.asSeconds();

	switch (mGameState) {

	// If on menu
	case GameState::MENU:
		mWindow.setMouseCursorVisible(true);
		if (mLmbWasCliked) {
			switch (mMenu.GetMenuChoice(mMousePosition)) {
			case MenuChoice::EXIT:
				mGameState = GameState::QUIT;
				break;
			case MenuChoice::LEVEL_1:
				mGameState = GameState::LEVEL;
				mLevel.LoadFromXML("Resource/Levels/Level1.xml", mWindow);
				// Load Level 1
				break;
			case MenuChoice::LEVEL_2:
				// Load Level 2
				break;
			case MenuChoice::LEVEL_3:
				// Load Level 3
				break;
			case MenuChoice::NONE:
			default:
				break;
			}
		}
		break;
	
	// If a level is loaded
	case GameState::LEVEL:
		mWindow.setMouseCursorVisible(false);
		mLevel.Update(mMousePosition, mWindow, dt);
		break;
	
	// If the game over screen is displayed
	case GameState::GAMEOVER:
		mWindow.setMouseCursorVisible(true);
		if (mLmbWasCliked) {
			switch (mGameOver.GetMenuChoice(mMousePosition))
			{
			case GameOverChoice::BACK_TO_MENU:
				mGameState = GameState::MENU;
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

void Game::Draw() {
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
		mLoadingScreen.Draw(mWindow);
		break;
	case GameState::MENU:
		mMenu.Draw(mWindow);
		break;
	case GameState::LEVEL:
		mLevel.Draw(mWindow);
		break;
	case GameState::GAMEOVER:
		mGameOver.Draw(mWindow);
		break;
	default:
		break;
	}

	// Swaps the back buffer
	mWindow.display();
}

void Game::Poll() {
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
			case sf::Keyboard::D:
				mGameState = GameState::GAMEOVER;
				break;
			case sf::Keyboard::A:
				mGameState = GameState::MENU;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mLmbWasCliked = true;
	}
	else {
		mLmbWasCliked = false;
	}
}