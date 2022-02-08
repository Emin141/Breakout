#include "Ball.h"

#include <random>
#include <cmath>

Ball::Ball() {
	srand(static_cast<unsigned int>(time(NULL)));
	mVelocity.x = static_cast<float>((rand() % 100));
	mVelocity.y = static_cast<float>((rand() % 100));
	NormalizeVelocity();
}

void Ball::UpdatePosition(const sf::RenderWindow& window, const float dt) {
	
	// Ball Collision with borders
	if ((mShape.getPosition().x - mShape.getOrigin().x) < 0) mVelocity.x *= -1.0f;
	if ((mShape.getPosition().y - mShape.getOrigin().y) < 0) mVelocity.y *= -1.0f;
	if ((mShape.getPosition().x + mShape.getOrigin().x) > window.getSize().x) mVelocity.x *= -1.0f;
	if ((mShape.getPosition().y + mShape.getOrigin().y) > window.getSize().y) mVelocity.y *= -1.0f;
	
	NormalizeVelocity();
	mPosition += mVelocity*dt;
	mShape.setPosition(mPosition);
}

void Ball::NormalizeVelocity() {
	float magnitude = sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y);
	mVelocity.x /= magnitude*0.002f;
	mVelocity.y /= magnitude*0.002f;
}