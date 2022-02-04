#include "Game.h"

Game::Game(void) {
	// Constructor call
	// Since the Window class which is a member of the Game class
	// already has a constructor, it will be called implicitly upon
	// creating Game in the main function, and the SDL2 window will open
	// automatically upon creation of the Game object
}

void Game::Initialize(void) {
	// XML parsing
	// Load assets
	// Setup scenes and actors
}

void Game::Run(void) {
	while (mWindow.isOpen()) {
		// Logic

		// Render logic
		mWindow.Draw();

		// Poll events
		mWindow.Poll();
	}
}

void Game::Quit(void) {
	// Unload assets
	// Deallocate all dynamic objects
	// Quit SDL and XML parsing
	// Return 0;
}

void Game::Update() {
	// Checks collision, HP, Score, Player lives, increases ball speed
	// This is also the function that gets the window events from the polling
	// and also the one that will handle scene changing, removing and adding
	// actors, and such.
}