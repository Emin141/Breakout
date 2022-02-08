#pragma once

#include "Scene.h"
#include "Paddle.h"
#include "Ball.h"

class Level : public Scene {
public:
	Level();
	// Temporary load method
	void Load(const sf::Vector2i& paddlePosition);
	// Method to load from XML file
	// Method to draw the scene
	void Draw(sf::RenderWindow& window);
	void Update(const sf::Vector2i& mousePosition, const sf::RenderWindow& window, const float dt);

private:
	// Paddle, ball, and some container for the bricks
	// Maybe the brick layout passed from XML?
	sf::Texture mPaddleTexture, mBallTexture;
	Paddle mPaddle;
	Ball mBall;
};

