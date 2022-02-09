#pragma once

#include "Entity.h"

class Ball : public Entity {
public:
	Ball();
	
	void UpdatePosition(const sf::RenderWindow& window, const float dt);
	void NormalizeVelocity();

	inline void XInvertVelocity() { mVelocity.x *= -1.0f; }
	inline void YInvertVelocity() { mVelocity.y *= -1.0f; }
	inline void Accelerate(const float acceleration, const float dt)
	{
		mVelocity.x += acceleration * dt;
		mVelocity.y += acceleration * dt;
	}
private:
	sf::Vector2f mVelocity;
};