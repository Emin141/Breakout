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
		"Resource/Textures/LoadingScreen.bmp"
	};
	mLoadingScreen.Load(LoadingScreenResources);
	mLoadingScreen.Draw(mWindowSurface);



	// Load assets
	std::list<std::string> MenuResources = {};
	std::list<std::string> LevelResources = {};
	std::list<std::string> GameOverResources = {};

	// XML parsing

	
	// Setup scenes and actors
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
				mGameState = GameState::QUIT;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
				case SDLK_q:
					mGameState = GameState::QUIT;
					break;
				}
				break;
			case SDL_MOUSEMOTION:
#ifdef DEBUG
				std::cout << "x position of cursor: " <<
					event.button.x << "\n";
#endif
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
	// This is also the function that gets the window events from the polling
	// and also the one that will handle scene changing, removing and adding
	// actors, and such.
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
		mLevel.Draw(mWindowSurface);
		break;
	case GameState::GAMEOVER:
		mGameOver.Draw(mWindowSurface);
		break;
	default:
		break;
	}
	SDL_UpdateWindowSurface(mWindowPtr);
}