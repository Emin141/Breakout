#include "Paddle.h"

void Paddle::SetPosition(const sf::Vector2i& position, const sf::RenderWindow& window) {

	float xPosition = static_cast<float>(position.x);
	if (position.x < (mShape.getSize().x/2.0f)) {
		xPosition = mShape.getSize().x/2.0f;
	}
	else if (position.x > (window.getSize().x - mShape.getSize().x/2.0f)) {
		xPosition = (static_cast<float>(window.getSize().x) - mShape.getSize().x/2.0f);
	}

	mPosition = sf::Vector2f( 
		xPosition, 
		static_cast<float>(window.getSize().y) - mShape.getSize().y/2.0f
	);
	mShape.setPosition(mPosition);
}
