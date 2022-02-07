#pragma once

#include "Scene.h"
#include <array>

class Button {
public:
	void Create(const sf::Font& font, const sf::Vector2f& position, const std::string& label);
	void Draw(sf::RenderWindow& window);
private:
	sf::Text mLabel;
	sf::RectangleShape mBody;
};


class Menu : Scene {
public:
	void Load(const sf::Font& font, const sf::Vector2f windowDimensions);
	void Draw(sf::RenderWindow& window);
private:
	sf::Text mTitle;
	std::array<Button, 4> mButton;
};