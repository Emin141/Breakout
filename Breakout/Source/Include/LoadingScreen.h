#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>

class LoadingScreen : Scene {
public:
	LoadingScreen() 
		: mText() {}
	void Load(const sf::Font& font, const sf::Vector2f& position);
	void Draw(sf::RenderWindow& window);
private:
	sf::Text mText;
};

