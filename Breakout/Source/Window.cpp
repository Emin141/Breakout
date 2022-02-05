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
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
	);
	if (mWindowPtr == nullptr) {
		std::cout << "SDL2 window failed to initialize with"
			" Error: " << SDL_GetError();
	}

	mWindowState = GameState::LOADING;
}

Window::~Window() {
	SDL_DestroyWindow(mWindowPtr);
	SDL_Quit();
}

void Window::Draw() {
	SDL_UpdateWindowSurface(mWindowPtr);
	// Draw scene
}

void Window::Poll() {
	SDL_Event Event;
	while (SDL_PollEvent(&Event) != 0) {
		switch (Event.type)
		{
		case SDL_QUIT:
			
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (Event.button.button == SDL_BUTTON_LEFT)
				std::cout << "Left button pressed\n";
			if (Event.button.button == SDL_BUTTON_RIGHT)
				std::cout << "Right button pressed\n";
			break;
		case SDL_MOUSEMOTION:
			// Will be passed to the location of the paddle
			std::cout << "x position: " << Event.button.x << "\n";
			break;
		default:
			break;
		}
	}
}