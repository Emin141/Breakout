#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class CollisionBox {
public:
	CollisionBox() : mCenter(0, 0), mSize(0, 0) {}
	CollisionBox(const sf::Vector2i& center, const sf::Vector2f& size)
		: mCenter(center), mSize(size) {}

	void CreateCollisionBox(const sf::Vector2i& center, const sf::Vector2f& size);

	inline sf::Vector2i GetCenter() const { return mCenter; }
	inline float GetWidth() const { return mSize.x; }
	inline float GetHeight() const { return mSize.y; }
	bool CheckCollision(const CollisionBox& otherCollisionBox) const;
private:
	sf::Vector2i mCenter;
	sf::Vector2f mSize;
};