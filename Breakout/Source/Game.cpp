#include "Game.h"

#include <iostream>

Game::Game() {
	// Constructor call
	mGameState = GameState::LOADING;
	mWindowPtr = nullptr;
	mWindowWidth = 800;
	mWindowHeight = 600;
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
	// XML parsing
	// Load assets
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
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				mGameState = GameState::QUIT;
				break;
			case SDL_MOUSEMOTION:
				std::cout << "x position of cursor: " <<
					event.button.x << "\n";
				break;
			default:
				break;
			}
		}
	}
}

void Game::Quit() {
	SDL_DestroyWindow(mWindowPtr);
	mWindowPtr = nullptr;
	SDL_Quit();

	// Unload assets
	// Deallocate all dynamic objects
	// XML parsing
	// Return 0;
}

void Game::Update() {
	// Checks collision, HP, Score, Player lives, increases ball speed
	// This is also the function that gets the window events from the polling
	// and also the one that will handle scene changing, removing and adding
	// actors, and such.
}

void Game::Draw() {
	// Draw the passed scene
	SDL_UpdateWindowSurface(mWindowPtr);
}