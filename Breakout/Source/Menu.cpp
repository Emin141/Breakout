#include "Menu.h"

void Button::Create(const sf::Font& font, const sf::Vector2f& position,
	const std::string& label){
	mLabel.setFont(font);
	mLabel.setString(label);
	mLabel.setCharacterSize(120);
	mLabel.setFillColor({ 140, 16, 16, 255 });
	mLabel.setOrigin(
		{
			mLabel.getLocalBounds().width / 2.0f,
			mLabel.getLocalBounds().height
		}
	);

	mBody.setFillColor({ 0x80, 0x80, 0x80, 255 });
	mBody.setSize({ 420, 160 });
	mBody.setOrigin(
		{
			mBody.getLocalBounds().width / 2.0f,
			mBody.getLocalBounds().height / 2.0f
		}
	);
	mBody.setPosition(position);
	mLabel.setPosition(position);
}

void Button::Draw(sf::RenderWindow& window) {
	window.draw(mBody);
	window.draw(mLabel);
}

void Menu::Load(const sf::Font& font, const sf::Vector2f windowDimensions) {
	mTitle.setFont(font);
	mTitle.setString("MAIN MENU");
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
		{windowDimensions.x/2.0f, 4.0f*windowDimensions.y/15.0f},
		"Level 1"
		);

	mButton[1].Create(
		font,
		{ windowDimensions.x / 2.0f, 7.0f * windowDimensions.y / 15.0f },
		"Level 2"
	);

	mButton[2].Create(
		font,
		{ windowDimensions.x / 2.0f, 10.0f * windowDimensions.y / 15.0f },
		"Level 3"
	);

	mButton[3].Create(
		font,
		{ windowDimensions.x / 2.0f, 13.0f * windowDimensions.y / 15.0f },
		"Exit"
	);
}

void Menu::Draw(sf::RenderWindow& window) {
	window.draw(mTitle);
	for (auto& B : mButton) B.Draw(window);
}