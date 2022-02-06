#include "Game.h"

#include <iostream>
#ifdef DEBUG
#include <SFML/System.hpp>
#endif

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
		sf::Style::Resize,
		ContextSettings
	);
	mWindowWidth = mWindow.getSize().x;
	mWindowHeight = mWindow.getSize().y;

	// Loading screen until the game is loaded
	std::list<std::string> LoadingScreenResources = {
		"Resource/Textures/Backgrounds/LoadingScreen.png"
	};
	mLoadingScreen.Load(LoadingScreenResources);
	mWindow.clear(sf::Color::Black);
	mLoadingScreen.Draw(mWindow);
	mWindow.display();

	// Load assets
	std::list<std::string> MenuResources = {
		"Resource/Textures/Backgrounds/Menu.png",
		"Resource/Textures/Backgrounds/Button_1.png",
		"Resource/Textures/Backgrounds/Button_2.png",
		"Resource/Textures/Backgrounds/Button_3.png",
		"Resource/Textures/Backgrounds/Button_exit.png"
	};
	mMenu.Load(MenuResources);

	std::list<std::string> GameOverResources = {
		"Resource/Textures/Backgrounds/GameOver.bmp"
	};
	mGameOver.Load(GameOverResources);


	std::list<std::string> LevelResources = {};

	// XML parsing


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
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}