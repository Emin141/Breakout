#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Main.hpp>

#include "Actor.h"

class Scene {
public:
	Scene();
	~Scene();
	virtual void Load(const std::vector<std::string>& resources,
		const std::vector<sf::Vector2f>& positions);
	//void AddActor(Actor& actor);
	//void RemoveActor(Actor& actor);
	void Draw(sf::RenderWindow& window);
private:
	std::vector<Actor*> mActorList;
};