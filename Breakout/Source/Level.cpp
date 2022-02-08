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
    //mPaddle.mCollisionBox.CreateCollisionBox();

	mBallTexture.loadFromFile("Resource/Textures/Ball.png");
	mBall.Create(
		mBallTexture,
		sf::Vector2f(32, 32),
		sf::Vector2f(1000, 880)
	);
	// mBall.mCollisionBox.CreateCollisionBox();
}

void Level::Draw(sf::RenderWindow& window) {
	mPaddle.Draw(window);
	mBall.Draw(window);
	// Draw all bricks
}

void Level::Update(const sf::Vector2i& mousePosition, const sf::RenderWindow& window, const float dt) {
	mPaddle.SetPosition(mousePosition, window);
	mBall.UpdatePosition(window, dt);
}
