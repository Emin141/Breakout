#pragma once

#include "Entity.h"

class Paddle : public Entity {
public:
	void setTexture(const sf::Texture texture);
	void setPosition
	(const sf::Vector2i& position, const sf::RenderWindow& window);
private:
	sf::Texture mTexture;
};