#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Actor {
public:
	Actor();
	~Actor();
	void create(const sf::Vector2f& size, const sf::Vector2f& position);
	void draw(sf::RenderWindow& window) const;
	
protected:
	sf::Vector2f mSize;
	sf::Vector2f mPosition;
	sf::RectangleShape mShape;
};