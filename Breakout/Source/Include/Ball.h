#pragma once

#ifdef V_DTOR_DEBUG
#include <plog/Log.h>
#endif

#include "Entity.h"

class Ball : public Entity {
public:
	Ball();
#ifdef V_DTOR_DEBUG
	virtual ~Ball() { PLOGD << "Ball destroyed! "; }
#else 
	virtual ~Ball() {}
#endif

	void setTexture(const sf::Texture texture);
	void updatePosition(const sf::RenderWindow& window, const float dt);
	void normalizeVelocity();
	void resetVelocity();
	inline void xInvertVelocity() { mVelocity.x *= -1.0f; }
	inline void yInvertVelocity() { mVelocity.y *= -1.0f; }
	void redirect(const float paddleCenterX, const float paddleSizeX);
	inline void rewindPosition() { mPosition = mPreviousPosition; mShape.setPosition(mPosition); }
private:
	sf::Vector2f mVelocity;
	sf::Texture mTexture;
};