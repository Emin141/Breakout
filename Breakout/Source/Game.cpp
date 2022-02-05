#include "Game.h"

Game::Game() {
	// Constructor call
	// Since the Window class which is a member of the Game class
	// already has a constructor, it will be called implicitly upon
	// creating Game in the main function, and the SDL2 window will open
	// automatically upon creation of the Game object
	mGameState = GameState::LOADING;
}

void Game::Initialize() {
	// XML parsing
	// Load assets
	// Setup scenes and actors
}

void Game::Run() {
	while (mGameState!=GameState::NOT_RUNNING) {
		// Logic

		// Render logic
		mWindow.Draw();

		// Poll events
		mWindow.Poll();
	}
}

void Game::Quit() {
	// Window is automatically closed by destructor call
	
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