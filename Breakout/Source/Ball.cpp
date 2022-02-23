#include "Ball.h"

#include <random>
#include <cmath>

Ball::Ball() {
	mVelocity = { 0.0f, 1000.0f };
	normalizeVelocity();
	mPreviousPosition = { 0.0f, 0.0f };
}

void Ball::setTexture(const sf::Texture texture) {
	// Not a reference because the texture object needs to live while the ball lives
	mTexture = texture;
	mShape.setTexture(&mTexture);
}

void Ball::updatePosition(const sf::RenderWindow& window, const float dt) {
	mPreviousPosition = mPosition;
	mPosition += mVelocity * dt;
	mShape.setPosition(mPosition);
}

void Ball::normalizeVelocity() {
	float scalingFactor = 0.002f;
	float magnitude = scalingFactor * sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y);
	mVelocity.x /= magnitude;
	mVelocity.y /= magnitude;
}

void Ball::resetVelocity() {
	mVelocity = { 0.0f, 1000.0f };
	normalizeVelocity();
	mPreviousPosition = { 0.0f, 0.0f };
}

void Ball::redirect(const float paddleCenterX, const float paddleSizeX) {
	/*

	Rediredction algorithm

	This is an algorithm that I came up with. Essentially, the ball shouldn't just
	bounce around with no control. That is okay for brick and wall collisions,
	but the player should be able to control the direction in which the ball will
	travel, in order to have some sense of control and aiming.

	The algorithm calculates the difference of the x coordinates at the paddle and
	ball centers. The value is then considered as an arguement to two functions
	that I also came up with. The direction can be at the leftmost collision point
	at a maximum angle of 45° to the left, and on the right side 45° to the right.

	In order to achieve this, these two functions MUST be trigonometric functions,
	anything else would violate the unit length of the direction vector (well,
	technically speaking they COULD be Taylor polynomials to a certain degree,
	but cmath's trig functions do the same thing anyways). Therefore, the minimum
	value of the X direciton is -sqrt(2)/2 and the maximum is sqrt(2)/2, whereas
	the bounds for Y are sqrt(2)/2 and sqrt(2)/2. Well, actually -sqrt(2)/2 and
	-sqrt(2)/2, but that is remedied by multiplying by -1.
	Thus, the Y value increases up to 1 (that is -1), then decreases again.

	In order to find these functions, I COULD do it all by hand, but I can't be
	bothered to reinvent the wheel, so I used GeoGebra for graphing the functions
	visually. I have also attached the file so it can be examined. At the end
	of the day I had to do it by hand anyways, but the file did help visualise.
	The functions are:

	x_component = sin(distance * pi/4)
	y_component = -cos(distance * pi/4)

	Here are the steps:

	1. Get the magnitude of the velocity vector. This magnitude is
	used to multiply the new unit vector after the algorithm.

	2. Get the difference of the ball x and the paddle x center.

	3. Divide the distance by half the paddle lenght. This way the argument is
	"normalized" to a range of [-1.0f, 1.0f]. (Has a bug?)

	4. Plug in the value to the trigonometric functions. Take care that they
	are also normalized to the pi radians standard.

	5. Check if the magnitude is very large, capped. If it is, don't increase it
	anymore. Otherwise increase the magnitude.

	6. Assign the values to the velocity vector and multiply them with the
	magnitude of the old velocity.

	7. Pat yourself on the back, flexing math, then be humbled when you
	realise that there is a bug with the length division lol
	luckily, it was easy to circumvent

	*/

	float pi = 4.0f * atan(1.0f); // Since atan(1) = pi/4...

	float magnitude = sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y);

	float distance = (mPosition.x + mSize.x) / 2.0f - paddleCenterX;

	// Scales the distance to be in [-1,1]
	distance = 4 * distance / paddleSizeX + 1;

	// Accelerates the ball up to a certain speed, exponentially
	// This way the game is easy at first, but gets harder faster later
	if (magnitude < 1500.0f) {
		magnitude *= 1.05f;
	}

	mVelocity.x = sin(distance * (pi / 3)) * magnitude;
	mVelocity.y = -cos(distance * (pi / 3)) * magnitude;
}