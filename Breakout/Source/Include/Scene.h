#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "Actor.h"

class Scene {
public:
	Scene();
	~Scene();
	virtual void Load(const std::list<std::string>& resources);
	//void AddActor(Actor& actor);
	//void RemoveActor(Actor& actor);
	void Draw(sf::RenderWindow& window);
private:
	std::list<Actor*> mActorList;
};