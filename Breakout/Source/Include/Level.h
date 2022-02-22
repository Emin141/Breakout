#pragma once

#include <list>
#include <array>

#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

class Level {
public:
	Level();
#include <iostream>
	~Level() { std::cout << "Level destructor called!\n"; }

	void loadFromXML(const std::string&, const sf::RenderWindow&);
	void arrangeBricks(const sf::RenderWindow&);
	void draw(sf::RenderWindow& window);
	void update(const sf::Vector2i&, const sf::RenderWindow&, const float, bool&);
	inline unsigned int getPlayerScore() const { return mPlayerScore; }

private:
	// Paddle info
	sf::Texture mPaddleTexture;
	Paddle mPaddle;

	// Ball info
	sf::Texture mBallTexture;
	Ball mBall;

	// Background 
	sf::Texture mBackgoundTexture;
	sf::RectangleShape mBackground;

	// Bricks info
	unsigned int mRowCount;
	unsigned int mColumnCount;
	unsigned int mRowSpacing;
	unsigned int mColumnSpacing;

	// Bricks assets
	std::array<Brick, 4> mBrick;
	std::array<sf::Texture, 4> mBrickTexture;
	std::array<sf::SoundBuffer, 4> mHitSoundBuffer;
	std::array<sf::SoundBuffer, 3> mBreakSoundBuffer;
	std::array<sf::Sound, 4> mHitSound;
	std::array<sf::Sound, 3> mBreakSound;
	std::array<unsigned int, 4> mBrickBreakScore;
	std::string mBrickLayout;

	std::list<Brick> mBrickList;

	// Player score tracker
	unsigned int mPlayerScore;
	unsigned int mBreakableBricksNum;
};

