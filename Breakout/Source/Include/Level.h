#pragma once

#include <list>
#include <unordered_map>

#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

class Level {
public:
	Level();

	void loadFromXML(const std::string& filename, const sf::RenderWindow& window);
	void arrangeBricks(const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void update(const sf::Vector2i& mousePosition, const sf::RenderWindow& window, const float dt, bool& gameIsOver);
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
	std::unordered_map<BrickID, Brick> mBrick;
	std::unordered_map<BrickID, sf::Texture> mBrickTexture;
	std::unordered_map<BrickID, sf::SoundBuffer> mHitSoundBuffer;
	std::unordered_map<BrickID, sf::SoundBuffer> mBreakSoundBuffer;
	std::unordered_map<BrickID, sf::Sound> mHitSound;
	std::unordered_map<BrickID, sf::Sound> mBreakSound;
	std::unordered_map<BrickID, unsigned int> mBrickBreakScore;
	std::string mBrickLayout;

	std::list<Brick> mBrickList;

	// Player score tracker
	unsigned int mPlayerScore;
	unsigned int mBreakableBricksNum;
};

