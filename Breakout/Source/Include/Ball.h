#pragma once

#include "Entity.h"

class Ball : public Entity {
public:
	Ball();
	
	void SetTexture(const sf::Texture texture);
	void UpdatePosition(const sf::RenderWindow& window, const float dt);
	void NormalizeVelocity();
	void ResetVelocity();
	inline void XInvertVelocity() { mVelocity.x *= -1.0f; }
	inline void YInvertVelocity() { mVelocity.y *= -1.0f; }
	void Redirect(const float, const float);
	inline void RewindPosition() { mPosition = mPreviousPosition; mShape.setPosition(mPosition); }
private:
	sf::Vector2f mVelocity;
	sf::Texture mTexture;
};