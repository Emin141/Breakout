#pragma once

#include "Scene.h"
#include "Paddle.h"

class Level : public Scene {
public:
	Level();
	// Temporary load method
	void TempLoad(sf::Texture& texture, const sf::Vector2i& position);
	// Method to load from XML file
	// Method to draw the scene
	void Draw(sf::RenderWindow& window);
	void SetPaddlePosition(const sf::Vector2i& position, const sf::RenderWindow& window);
private:
	// Paddle, ball, and some container for the bricks
	// Maybe the brick layout passed from XML?
	Paddle mPaddle;
};

