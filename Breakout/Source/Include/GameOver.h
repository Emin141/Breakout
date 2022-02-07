#pragma once

#include <array>

#include "Scene.h"
#include "Button.h"

enum class GameOverChoice {
	BACK_TO_MENU = 0,
	EXIT,
	NONE
};

class GameOver : public Scene {
public:
	void Load(const sf::Font& font, const sf::Vector2f windowDimensions);

	void Draw(sf::RenderWindow& window);

	GameOverChoice GetMenuChoice(const sf::Vector2i& mousePosition) const;
private:
	sf::Text mTitle;
	std::array<Button, 2> mButton;
};

