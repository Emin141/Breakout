#pragma once

#include <array>

#include "Scene.h"
#include "Button.h"

enum class GameOverChoice {
	BACK_TO_MENU = 0,
	EXIT,
	NONE
};

class GameOver : public Scene {
public:
	GameOver() : mPlayerScore(0) {}

	void load(const sf::Font& font, const sf::Vector2f windowDimensions, const sf::Texture& backgroundTexture);
	void draw(sf::RenderWindow& window);

	inline void updatePlayerScore(const unsigned int playerScore) { mPlayerScore = playerScore; }
	GameOverChoice getMenuChoice(const sf::Vector2i& mousePosition) const;

private:
	sf::Text mTitle;
	sf::Text mScoreDisplay;
	std::array<Button, 2> mButton;
	sf::RectangleShape mBackground;

	unsigned int mPlayerScore;
};

