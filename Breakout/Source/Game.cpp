#include "Game.h"

#include <iostream>

Game::Game() {
	// Constructor call
	mGameState = GameState::LOADING;
	mWindowPtr = nullptr;
	mWindowSurface = nullptr;
	mWindowWidth = 1600;
	mWindowHeight = 1200;

	// Scenes are implicitly initialized
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL failed to init with error: " <<
			SDL_GetError();
		std::cin.get();
		exit(-1);
	}
	
	mWindowPtr = SDL_CreateWindow(
		"Breakout",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		mWindowWidth,
		mWindowHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	if (mWindowPtr == nullptr) {
		std::cout << "Failed to create window with error: " <<
			SDL_GetError();
		std::cin.get();
		exit(-1);
	}

	mWindowSurface = SDL_GetWindowSurface(mWindowPtr);
	
	// Loading screen until the game is loaded
	std::list<std::string> LoadingScreenResources = {
		"Resource/Textures/Backgrounds/LoadingScreen.bmp"
	};
	mLoadingScreen.Load(LoadingScreenResources);
	mLoadingScreen.Draw(mWindowSurface);
	SDL_UpdateWindowSurface(mWindowPtr);


	// Load assets
	std::list<std::string> MenuResources = {
		"Resource/Textures/Backgrounds/Menu.bmp"
	};
	mMenu.Load(MenuResources);

	std::list<std::string> GameOverResources = {
		"Resource/Textures/Backgrounds/GameOver.bmp"
	};
	mGameOver.Load(GameOverResources);


	std::list<std::string> LevelResources = {};

	// XML parsing

	
	// Setup scenes and actors

#ifdef DEBUG
	SDL_Delay(2000);
#endif

	mGameState = GameState::MENU;
}

void Game::Run() {
	SDL_Event event;

	while (mGameState!=GameState::QUIT) {
		// Logic
		Update();

		// Render logic
		Draw();

		// Poll events
		// Better to be done inside this function instead of doing it like
		// Poll(). If done as Poll(), there needs to be another layer of 
		// unneccessary abstraction on the event type.
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
				case SDLK_q:
					mGameState = GameState::QUIT;
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				break;
			default:
				break;
			}
		}
	}
}

void Game::Quit() {
	// Unload assets
	SDL_FreeSurface(mWindowSurface);
	mWindowSurface = nullptr;

	// Deallocate all dynamic objects
	// XML parsing

	SDL_DestroyWindow(mWindowPtr);
	mWindowPtr = nullptr;
	SDL_Quit();
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
	// Draw the passed scene
	switch (mGameState) {
	case GameState::LOADING:
		mLoadingScreen.Draw(mWindowSurface);
		break;
	case GameState::MENU:
		mMenu.Draw(mWindowSurface);
		break;
	case GameState::LEVEL:
		//mLevel.Draw(mWindowSurface);
		break;
	case GameState::GAMEOVER:
		mGameOver.Draw(mWindowSurface);
		break;
	default:
		break;
	}
	SDL_UpdateWindowSurface(mWindowPtr);
}