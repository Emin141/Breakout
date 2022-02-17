#pragma once

#include "Scene.h"
#include "Button.h"
#include <array>

enum class MenuChoice {
	LEVEL_1 = 0,
	LEVEL_2,
	LEVEL_3,
	EXIT,
	NONE
};

class Menu : Scene {
public:
	void load(const sf::Font& font, const sf::Vector2f windowDimensions, const sf::Texture& backgroundTexture);
	void draw(sf::RenderWindow& window);
	MenuChoice getMenuChoice(const sf::Vector2i& mousePosition) const;

private:
	sf::Text mTitle;
	std::array<Button, 4> mButton;
	sf::RectangleShape mBackground;
};

