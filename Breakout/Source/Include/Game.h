#pragma once

#include "Window.h"

class Game {
public:
	Game(void);
	void Initialize(void);
	void Run(void);
	void Quit(void);
private:
	void Update(); // All logic is updated in the Game class
private:
	Window mWindow;

};