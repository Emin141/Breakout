#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Actor {
public:
	Actor();
	~Actor();
	void Create(sf::Texture& texture, const sf::Vector2f& size, const sf::Vector2f& position);
	void Draw(sf::RenderWindow& window) const;
	
protected:
	sf::Vector2f mSize;
	sf::Vector2f mPosition;
	sf::RectangleShape mShape;
	sf::Texture mTexture;
};