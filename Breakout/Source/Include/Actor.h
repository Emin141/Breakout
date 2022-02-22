#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#ifdef V_DTOR_DEBUG
#include <plog/Log.h>
#endif

class Actor {
public:
	Actor();
#ifdef V_DTOR_DEBUG
	virtual ~Actor() { PLOGD << "- Actor destroyed!"; }
#else
	virtual ~Actor() {}
#endif

	void create(const sf::Vector2f& size, const sf::Vector2f& position);
	void draw(sf::RenderWindow& window) const;

protected:
	sf::Vector2f mSize;
	sf::Vector2f mPosition;
	sf::RectangleShape mShape;
};