#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
	void Create(const sf::Font& font, const sf::Vector2f& position, const std::string& label);
	void Draw(sf::RenderWindow& window);
	bool HasMouseInside(const sf::Vector2i& point) const;
private:
	sf::Text mLabel;
	sf::RectangleShape mBody;
};
