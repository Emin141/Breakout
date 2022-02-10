#include "Ball.h"

#include <random>
#include <cmath>

Ball::Ball() {
	mVelocity = { 0.0f, 1000.0f };
	NormalizeVelocity();
	mPreviousPosition = { 0.0f, 0.0f };
}

void Ball::UpdatePosition(const sf::RenderWindow& window, const float dt) {
	mPreviousPosition = mPosition;
	mPosition += mVelocity*dt;
	mShape.setPosition(mPosition);
}

void Ball::NormalizeVelocity() {
	float magnitude = sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y);
	mVelocity.x /= magnitude*0.002f;
	mVelocity.y /= magnitude*0.002f;
}