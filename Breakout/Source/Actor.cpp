#include "Actor.h"

Actor::Actor() {
	mImageSurface = nullptr;
	mXPos = 0; mYPos = 0;
	mWidth = 0; mHeight = 0;
	mID = 0; // Invalid ID
}

Actor::~Actor() {
	SDL_FreeSurface(mImageSurface);
}

void Actor::Load(const std::string& assetPath) {
	mImageSurface = SDL_LoadBMP(assetPath.c_str());
	if (mImageSurface == nullptr) {
		std::cout << SDL_GetError() << "\n";
		std::cin.get();
		exit(-1);
	}
}

void Actor::Draw(SDL_Surface* windowSurface) {
	SDL_BlitSurface(
		mImageSurface,
		nullptr,
		windowSurface,
		nullptr
	);
}