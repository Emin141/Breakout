#include "Actor.h"

uint8_t Actor::ActorCount = 0;

Actor::Actor() {
	mPosition.x = 0.0f;
	mPosition.y = 0.0f;
	mScale.x = 1.0f;
	mScale.y = 1.0f;
	mID = 0;
}

Actor::~Actor() {
	DecreaseActorCount();
}

void Actor::Load(const std::string& assetPath,
	const sf::Vector2f& position) {
	
	mPosition = position;
	if (!mTexture.loadFromFile(assetPath)) {
		std::cout << "Failed to load texture at " <<
			assetPath << "\n";
		std::cin.get();
		exit(-1);
	}
	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPosition);
	mSprite.setScale(mScale);
	
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