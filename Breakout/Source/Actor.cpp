#include "Actor.h"

uint8_t Actor::mID = 0;

Actor::Actor() {
	mImageSurface = nullptr;
	mXPos = 0; mYPos = 0;
	mWidth = 0; mHeight = 0;
}

Actor::~Actor() {
	DecreaseActorCount();
	SDL_FreeSurface(mImageSurface);
}

void Actor::Load(const std::string& assetPath) {
	mImageSurface = SDL_LoadBMP(assetPath.c_str());
	if (mImageSurface == nullptr) {
		std::cout << SDL_GetError() << "\n";
		std::cin.get();
		exit(-1);
	}
	IncreaseActorCount();
}

void Actor::Draw(SDL_Surface* windowSurface) {
	SDL_BlitSurface(
		mImageSurface,
		nullptr,
		windowSurface,
		nullptr
	);
}

void Actor::IncreaseActorCount() {
	mID++;
#ifdef DEBUG
	std::cout << "Current actor count: " << static_cast<int>(mID) << "\n";
#endif
}

void Actor::DecreaseActorCount() {
	mID--;
#ifdef DEBUG
	std::cout << "Current actor count: " << static_cast<int>(mID) << "\n";
#endif
}