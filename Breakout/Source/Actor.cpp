#include "Actor.h"

uint8_t Actor::ActorCount = 0;

Actor::Actor() {
	mXPos = 0; mYPos = 0;
	mWidth = 0; mHeight = 0;
	mID = 0;
}

Actor::~Actor() {
	DecreaseActorCount();
}

void Actor::Load(const std::string& assetPath) {
	if (!mTexture.loadFromFile(assetPath)) {
		std::cout << "Failed to load texture at " <<
			assetPath << "\n";
		std::cin.get();
		exit(-1);
	}

	mSprite.setTexture(mTexture);
	IncreaseActorCount();
	mID = ActorCount;
}

void Actor::Draw(sf::RenderWindow& window) {
	window.draw(mSprite);
}

void Actor::IncreaseActorCount() {
	std::cout << "Current actor count " 
		<< static_cast<int>(++ActorCount) << "\n";
}

void Actor::DecreaseActorCount() {
	std::cout << "Current actor count "
		<< static_cast<int>(--ActorCount) << "\n";
}