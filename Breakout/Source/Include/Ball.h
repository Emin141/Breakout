#pragma once

#include "Entity.h"

class Ball : public Entity {
public:
	Ball();

	void setTexture(const sf::Texture texture);
	void updatePosition(const sf::RenderWindow& window, const float dt);
	void normalizeVelocity();
	void resetVelocity();
	inline void xInvertVelocity() { mVelocity.x *= -1.0f; }
	inline void yInvertVelocity() { mVelocity.y *= -1.0f; }
	void redirect(const float, const float);
	inline void rewindPosition() { mPosition = mPreviousPosition; mShape.setPosition(mPosition); }
private:
	sf::Vector2f mVelocity;
	sf::Texture mTexture;
};