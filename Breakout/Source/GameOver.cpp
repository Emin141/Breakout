#include "GameOver.h"
#include <iostream>

void GameOver::load(const sf::Font& font, const sf::Vector2f windowDimensions) {
	// Title options
	mTitle.setFont(font);
	mTitle.setString("GAME OVER");
	mTitle.setCharacterSize(100);
	mTitle.setFillColor(sf::Color(140, 16, 16, 255));
	mTitle.setOrigin(
		{
			mTitle.getLocalBounds().width / 2.0f,
			mTitle.getLocalBounds().height
		}
	);
	mTitle.setPosition(
		{
			windowDimensions.x / 2.0f,
			windowDimensions.y / 12.0f
		}
	);

	// Score options
	mScoreDisplay.setFont(font);
	mScoreDisplay.setString("SCORE: " + std::to_string(mPlayerScore));
	mScoreDisplay.setCharacterSize(100);
	mScoreDisplay.setFillColor(sf::Color(0xFF, 0xFF, 0xFF, 0xFF));
	mScoreDisplay.setOrigin(
		{
			mScoreDisplay.getLocalBounds().width / 2.0f,
			mScoreDisplay.getLocalBounds().height
		}
	);
	mScoreDisplay.setPosition(
		{
			windowDimensions.x / 2.0f,
			3.0f * windowDimensions.y / 12.0f
		}
	);

	// Buttons
	mButton[0].create(
		font,
		{ windowDimensions.x / 2.0f, 7.0f * windowDimensions.y / 15.0f },
		"MENU"
	);

	mButton[1].create(
		font,
		{ windowDimensions.x / 2.0f, 10.0f * windowDimensions.y / 15.0f },
		"EXIT"
	);
}

void GameOver::draw(sf::RenderWindow& window) {
	window.draw(mTitle);
	mScoreDisplay.setString("SCORE: " + std::to_string(mPlayerScore));
	window.draw(mScoreDisplay);
	for (auto& button : mButton) button.draw(window);
}

GameOverChoice GameOver::getMenuChoice(const sf::Vector2i& mousePosition) const {
	for (int i = 0; i < 2; i++) {
		if (mButton[i].hasMouseInside(mousePosition))
			return static_cast<GameOverChoice>(i);
	}
	// if none pass
	return GameOverChoice::NONE;
}