#include "Menu.h"

void Menu::load(const sf::Font& font, const sf::Vector2f windowDimensions) {
	mTitle.setFont(font);
	mTitle.setString("MAIN MENU");
	mTitle.setCharacterSize(windowDimensions.y / 10.0f);
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

	mButton[0].create(
		font,
		{ windowDimensions.x / 2.0f, 4.0f * windowDimensions.y / 15.0f },
		{ windowDimensions.x / 4.0f, windowDimensions.y / 6.0f },
		"LEVEL 1"
	);

	mButton[1].create(
		font,
		{ windowDimensions.x / 2.0f, 7.0f * windowDimensions.y / 15.0f },
		{ windowDimensions.x / 4.0f, windowDimensions.y / 6.0f },
		"LEVEL 2"
	);

	mButton[2].create(
		font,
		{ windowDimensions.x / 2.0f, 10.0f * windowDimensions.y / 15.0f },
		{ windowDimensions.x / 4.0f, windowDimensions.y / 6.0f },
		"LEVEL 3"
	);

	mButton[3].create(
		font,
		{ windowDimensions.x / 2.0f, 13.0f * windowDimensions.y / 15.0f },
		{ windowDimensions.x / 4.0f, windowDimensions.y / 6.0f },
		"EXIT"
	);
}

void Menu::draw(sf::RenderWindow& window) {
	window.draw(mTitle);
	for (auto& button : mButton) button.draw(window);
}

MenuChoice Menu::getMenuChoice(const sf::Vector2i& mousePosition) const {
	for (int menuChoice = 0; menuChoice < 4; menuChoice++) {
		if (mButton[menuChoice].hasMouseInside(mousePosition))
			return static_cast<MenuChoice>(menuChoice);
	}
	// if none pass
	return MenuChoice::NONE;
}