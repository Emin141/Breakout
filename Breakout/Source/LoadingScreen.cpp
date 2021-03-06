#include  "LoadingScreen.h"

void LoadingScreen::load(const sf::Font& font, const sf::Vector2f& position) {
	mText.setFont(font);
	mText.setString("LOADING...");
	mText.setCharacterSize(240);
	mText.setFillColor(sf::Color(0xFF, 0xA0, 0x10, 0xFF));
	mText.setOrigin(
		{
			mText.getLocalBounds().width / 2.0f,
			mText.getLocalBounds().height
		}
	);
	mText.setPosition(position);
}

void LoadingScreen::draw(sf::RenderWindow& window) {
	window.draw(mText);
}