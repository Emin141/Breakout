#include "Button.h"

void Button::create(const sf::Font& font, const sf::Vector2f& position,
	const sf::Vector2f& size, const std::string& label) {
	mLabel.setFont(font);
	mLabel.setString(label);
	mLabel.setCharacterSize(size.y / 2.0f);
	mLabel.setFillColor(sf::Color(0xFF, 0xA0, 0x10, 0xFF));
	mLabel.setOrigin(
		{
			mLabel.getLocalBounds().width / 2.0f,
			mLabel.getLocalBounds().height
		}
	);

	mBody.setFillColor({ 0x80, 0x80, 0x80, 0x80 });
	mBody.setSize(size);
	mBody.setOrigin(
		{
			mBody.getLocalBounds().width / 2.0f,
			mBody.getLocalBounds().height / 2.0f
		}
	);
	mBody.setPosition(position);
	mLabel.setPosition(position);
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(mBody);
	window.draw(mLabel);
}

bool Button::hasMouseInside(const sf::Vector2i& point) const {
	// Checks whether the mouse is inside the body of the button
	// Huge one-liner condition, but it would otherwise have to be nested
	if (
		point.x < (mBody.getPosition().x + mBody.getOrigin().x) && point.x >(mBody.getPosition().x - mBody.getOrigin().x)
		&&
		point.y < (mBody.getPosition().y + mBody.getOrigin().y) && point.y >(mBody.getPosition().y - mBody.getOrigin().y)
		) return true;
	// No need for an else statement
	return false;
}