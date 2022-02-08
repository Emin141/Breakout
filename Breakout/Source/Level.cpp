#include "Level.h"

Level::Level() {

}

void Level::TempLoad(sf::Texture& texture, const sf::Vector2i& position) {
	mPaddle.Create(
		texture,
		sf::Vector2f(200, 25),
		sf::Vector2f(position.x, position.y)
	);
	// mPaddle.mCollisionBox.CreateCollisionBox();
}

void Level::Draw(sf::RenderWindow& window) {
	mPaddle.Draw(window);
	// mBall.Draw(window)
	// Draw all bricks
}

void Level::SetPaddlePosition(const sf::Vector2i& position, const sf::RenderWindow& window) {
	mPaddle.SetPosition(position, window);
}
