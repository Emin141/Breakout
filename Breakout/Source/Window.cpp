#include "Window.h"

#include <SDL.h>
#include <iostream>

Window::Window() {
	// Default values for the window width and height
	// These need to be tracked because of positional rendering

	mWidth = 800;
	mHeight = 600;

	// SDL Initialization
	// Might have not initialized everything, but I use almost everything anyways so...
	if (SDL_Init(SDL_INIT_EVERYTHING)!=0) {
		// Debug statements need to be rerouted to loggers
		std::cout << "SDL2 failed to initialize. Maybe change the"
			" init flags? Error: " << SDL_GetError();
	}
	std::cout << "SDL2 successfully initialized with all flags\n";
	
	mWindowPtr = SDL_CreateWindow(
		"Breakout",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		mWidth,
		mHeight,
		SDL_WINDOW_RESIZABLE
	);

	openStatus = true;
}

void Window::Draw() {

}

void Window::Poll() {
	while (SDL_PollEvent(&mEvent) != 0) {
		switch (mEvent.window.event)
		{
		case SDL_QUIT:
			openStatus = false;
			break;
		default:
			break;
		}
	}
}