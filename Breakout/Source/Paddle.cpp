#include "Paddle.h"

void Paddle::SetPosition(const sf::Vector2i& position, const sf::RenderWindow& window) {

	float xPosition = static_cast<float>(position.x);
	if (position.x < 0) {
		xPosition = 0;
	}
	else if (position.x > (window.getSize().x - mShape.getSize().x)) {
		xPosition = (static_cast<float>(window.getSize().x) - mShape.getSize().x);
	}

	mPosition = sf::Vector2f( 
		xPosition, 
		static_cast<float>(window.getSize().y) - mShape.getSize().y
	);
	mShape.setPosition(mPosition);
}