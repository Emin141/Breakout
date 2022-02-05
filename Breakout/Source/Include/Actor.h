#pragma once

#include <iostream>
#include <SDL.h>

class Actor {
public:
	~Actor();
	void Load(const std::string& assetPath);
	void Draw(SDL_Surface* windowSurface);
private:
	// Image
	SDL_Surface* mImageSurface;
	// Position
	// Dimensions
};