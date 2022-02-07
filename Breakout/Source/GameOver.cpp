#include "GameOver.h"

void GameOver::Load(const sf::Font& font, const sf::Vector2f windowDimensions) {
	mTitle.setFont(font);
	mTitle.setString("GAME OVER");
	mTitle.setCharacterSize(120);
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

	mButton[0].Create(
		font,
		{ windowDimensions.x / 2.0f, 4.0f * windowDimensions.y / 15.0f },
		"MENU"
	);

	mButton[1].Create(
		font,
		{ windowDimensions.x / 2.0f, 7.0f * windowDimensions.y / 15.0f },
		"EXIT"
	);
}

void GameOver::Draw(sf::RenderWindow& window) {
	window.draw(mTitle);
	for (auto& button : mButton) button.Draw(window);
}

GameOverChoice GameOver::GetMenuChoice(const sf::Vector2i& mousePosition) const {
	for (int i = 0; i < 2; i++) {
		if (mButton[i].HasMouseInside(mousePosition))
			return static_cast<GameOverChoice>(i);
	}
	// if none pass
	return GameOverChoice::NONE;
}