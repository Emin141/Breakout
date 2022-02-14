#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>

class LoadingScreen : public Scene {
public:
	LoadingScreen()
		: mText() {}
	void load(const sf::Font& font, const sf::Vector2f& position);
	void draw(sf::RenderWindow& window);
private:
	sf::Text mText;
};

