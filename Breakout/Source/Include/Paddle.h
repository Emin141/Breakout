#pragma once

#include "Entity.h"

class Paddle : public Entity {
public:
	Paddle() : mTexture() {}
	void SetPosition(const sf::Vector2i& position, const sf::RenderWindow& window);
private:
	sf::Texture mTexture;
};