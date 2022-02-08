#include "Menu.h"

void Menu::Load(const sf::Font& font, const sf::Vector2f windowDimensions) {
	mTitle.setFont(font);
	mTitle.setString("MAIN MENU");
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

	mButton[0].Create(
		font,
		{windowDimensions.x/2.0f, 4.0f*windowDimensions.y/15.0f},
		"LEVEL 1"
		);

	mButton[1].Create(
		font,
		{ windowDimensions.x / 2.0f, 7.0f * windowDimensions.y / 15.0f },
		"LEVEL 2"
	);

	mButton[2].Create(
		font,
		{ windowDimensions.x / 2.0f, 10.0f * windowDimensions.y / 15.0f },
		"LEVEL 3"
	);

	mButton[3].Create(
		font,
		{ windowDimensions.x / 2.0f, 13.0f * windowDimensions.y / 15.0f },
		"EXIT"
	);
}

void Menu::Draw(sf::RenderWindow& window) {
	window.draw(mTitle);
	for (auto& button : mButton) button.Draw(window);
}

MenuChoice Menu::GetMenuChoice(const sf::Vector2i& mousePosition) const {
	for (int i = 0; i < 4; i++) {
		if (mButton[i].HasMouseInside(mousePosition))
			return static_cast<MenuChoice>(i);
	}
	// if none pass
	return MenuChoice::NONE;
}