#include "Game.h"

#include <iostream>
#include "LoadingScreen.h"

Game::Game() {
	// Constructor call
	mGameState = GameState::LOADING;

	sf::ContextSettings ContextSettings;
	ContextSettings.antialiasingLevel = 4;
	ContextSettings.majorVersion = 3;
	ContextSettings.minorVersion = 3;

	mWindow.create(
		sf::VideoMode(1920, 1080),
		"Breakout",
		sf::Style::Fullscreen,
		ContextSettings
	);
	mWindowWidth = mWindow.getSize().x;
	mWindowHeight = mWindow.getSize().y;

	mFont.loadFromFile("Resource/Fonts/Biolinum.ttf");

	// Loading screen until the game is loaded
	mLoadingScreen.Load(mFont, 
		{ mWindowWidth / 2.0f, mWindowHeight / 2.0f });
	mWindow.clear(sf::Color::Black);
	mLoadingScreen.Draw(mWindow);
	mWindow.display();

	// Menu screen
	mMenu.Load(mFont, sf::Vector2f(mWindowWidth, mWindowHeight));

	// Game over screen
	


	// Setup scenes and actors

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
	switch (mGameState) {
	case GameState::MENU:
		break;
	case GameState::LEVEL:
		break;
	case GameState::GAMEOVER:
		break;
	default:
		break;
	}
}

void Game::Draw() {
	mWindow.clear(sf::Color::Black);
	switch (mGameState) {
	case GameState::LOADING:
		mLoadingScreen.Draw(mWindow);
		break;
	case GameState::MENU:
		mMenu.Draw(mWindow);
		break;
	case GameState::LEVEL:
		//mLevel.Draw(mWindowSurface);
		break;
	case GameState::GAMEOVER:
		mGameOver.Draw(mWindow);
		break;
	default:
		break;
	}
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
				using Key = sf::Keyboard;
			case Key::Escape:
			case Key::Q:
				mGameState = GameState::QUIT;
				break;
			case Key::A:
				mGameState = GameState::GAMEOVER;
				break;
			case Key::D:
				mGameState = GameState::LOADING;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}