#include "Level.h"

Level::Level() {

}

void Level::Load(const sf::Vector2i& position) {
	mPaddleTexture.loadFromFile("Resource/Textures/Paddle.png");
	mPaddle.Create(
		mPaddleTexture,
		sf::Vector2f(200, 25),
		sf::Vector2f(position.x, position.y)
	);

	mBallTexture.loadFromFile("Resource/Textures/Ball.png");
	mBall.Create(
		mBallTexture,
		sf::Vector2f(32, 32),
		sf::Vector2f(1000, 500)
	);
}

void Level::Draw(sf::RenderWindow& window) {
	mPaddle.Draw(window);
	mBall.Draw(window);
	// Draw all bricks
}

void Level::Update(const sf::Vector2i& mousePosition, const sf::RenderWindow& window, const float dt) {
	mPaddle.SetPosition(mousePosition, window);

	// Ball Collision with borders
	if (mBall.GetPosition().x < 0) mBall.XInvertVelocity();
	if (mBall.GetPosition().y < 0) mBall.YInvertVelocity();
	if ((mBall.GetPosition().x + mBall.GetSize().x) > window.getSize().x) mBall.XInvertVelocity();
	
	// Loss condition:
	if ((mBall.GetPosition().y + mBall.GetSize().y) > window.getSize().y) mBall.YInvertVelocity();


	if (mBall.CollidedWith(mPaddle)) 
	{
		mBall.YInvertVelocity();

		// Kicks the ball out of the collision box
		mBall.SetPosition(
			{
				mBall.GetPosition().x, 
				mPaddle.GetPosition().y - mBall.GetSize().y - 1.0f
			}
		);
	}

	mBall.UpdatePosition(window, dt);
}
