#pragma once

// Entities are just actors with collision checking
// However, new classes can be inherited from the entity class
// All three are special: 
// 
// Bricks can't move and have hitpoints
// The ball moves constantly
// The paddle moves on mouse control

#include "Actor.h"

class Entity : public Actor {
public:
	Entity();

	bool CollidedWith(const Entity& otherEntity) const;

	inline void SetPosition(const sf::Vector2f& position) { mPosition = position; }
	inline void SetSize(const sf::Vector2f& size) { mSize = size; }
	inline sf::Vector2f GetPosition() const { return mPosition; }
	inline sf::Vector2f GetSize() const { return mSize; }
private:
};

