#pragma once

#include "Scene.h"

class Menu : Scene {
public:
	void Load(const std::list<std::string>& resources);
	void Draw(sf::RenderWindow& window);
private:
};
