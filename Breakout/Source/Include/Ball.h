#pragma once

#include "Entity.h"

class Ball : public Entity {
public:
	Ball();
	void UpdatePosition(const sf::RenderWindow& window, const float dt);
	void NormalizeVelocity();
private:
	sf::Vector2f mVelocity;
};