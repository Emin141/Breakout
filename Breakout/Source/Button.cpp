#include "Button.h"

void Button::Create(const sf::Font& font, const sf::Vector2f& position,
	const std::string& label) {
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

bool Button::HasMouseInside(const sf::Vector2i& point) const {
	// Huge condition incomming
	if (
		point.x < (mBody.getPosition().x + mBody.getOrigin().x) && point.x >(mBody.getPosition().x - mBody.getOrigin().x)
		&&
		point.y < (mBody.getPosition().y + mBody.getOrigin().y) && point.y >(mBody.getPosition().y - mBody.getOrigin().y)
		) return true;
	return false;
}