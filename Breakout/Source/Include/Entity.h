#pragma once

// Entities are just actors with collision checking
// However, new classes can be inherited from the entity class
// All three are special: 
// 
// Bricks can't move and have hitpoints
// The ball moves constantly
// The paddle moves on mouse control

#include "Actor.h"

enum class CollisionSide {
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	NONE
};

class Entity : public Actor {
public:
	Entity() : mPreviousPosition({0.0f, 0.0f}) {}

	bool collidedWith(const Entity&, CollisionSide&) const;

	bool operator==(const Entity&) const;
	bool operator!=(const Entity&) const;

	inline void setPosition(const sf::Vector2f& position) { mPreviousPosition = mPosition; mPosition = position; mShape.setPosition(mPosition); }
	inline void setSize(const sf::Vector2f& size) { mSize = size; mShape.setSize(mSize); }
	inline sf::Vector2f getPosition() const { return mPosition; }
	inline sf::Vector2f getSize() const { return mSize; }
	inline sf::Vector2f getPreviousPosition() const { return mPreviousPosition; }
	inline sf::Vector2f getCenter() const {
		return sf::Vector2f(
			(mPosition.x + mSize.x)/2.0f,
			(mPosition.y + mSize.y)/2.0f
		);
	}
protected:
	sf::Vector2f mPreviousPosition;
};

