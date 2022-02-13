#include "Actor.h"

Actor::Actor() {
	mPosition = { 0.0f, 0.0f };
	mSize = { 0.0f, 0.0f };
	mShape.setSize(mSize);
	mShape.setPosition(mPosition);
}

Actor::~Actor() {
}

void Actor::Create(const sf::Vector2f& size, const sf::Vector2f& position) {
	mSize = size;
	mPosition = position;
	mShape.setSize(mSize);
	mShape.setPosition(mPosition);
}

void Actor::Draw(sf::RenderWindow& window) const {
	window.draw(mShape);
}