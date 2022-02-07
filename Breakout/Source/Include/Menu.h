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
	void Load(const sf::Font& font, const sf::Vector2f windowDimensions);
	
	void Draw(sf::RenderWindow& window);

	MenuChoice GetMenuChoice(const sf::Vector2i& mousePosition) const;
private:
	sf::Text mTitle;
	std::array<Button, 4> mButton;
};

