#pragma once

#include <list>
#include <array>

#include "Scene.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

class Level : public Scene {
public:
	Level();
	void LoadFromXML(const std::string&, const sf::RenderWindow&);
	void ArrangeBricks(const sf::RenderWindow&);
	void Draw(sf::RenderWindow& window);
	void Update(const sf::Vector2i& mousePosition, const sf::RenderWindow& window, const float dt);

private:
	// Paddle info
	sf::Texture mPaddleTexture;
	Paddle mPaddle;

	// Ball info
	sf::Texture mBallTexture;
	Ball mBall;

	// Bricks info
	unsigned int mRowCount;
	unsigned int mColumnCount;
	unsigned int mRowSpacing;
	unsigned int mColumnSpacing;
	sf::Texture mBackgoundTexture;
	std::array<Brick, 4> mBrick;
	std::string mBrickLayout;

	std::list<Brick> mBrickList;
};

