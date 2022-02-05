#pragma once

#include <iostream>
#include <SDL.h>

class Actor {
public:
	Actor();
	~Actor();
	void Load(const std::string& assetPath);
	void Draw(SDL_Surface* windowSurface);
	inline uint8_t GetID() const { return mID; }
	static void IncreaseActorCount();
	static void DecreaseActorCount();
	static uint8_t mID;
private:
	SDL_Surface* mImageSurface;
	uint16_t mXPos, mYPos;
	uint16_t mWidth, mHeight;
};