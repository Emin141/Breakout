#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
	void create(const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& label);
	void draw(sf::RenderWindow& window);
	bool hasMouseInside(const sf::Vector2i& point) const;

private:
	sf::Text mLabel;
	sf::RectangleShape mBody;
};
