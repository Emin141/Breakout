#pragma once

#include <SDL.h>
#include <list>

#include "Actor.h"

class Scene {
public:
	Scene();
	~Scene();
	void Load(const std::list<std::string>& resources);
	void AddActor(Actor& actor);
	void RemoveActor(Actor& actor);
	void Draw(SDL_Surface* windowSurface);
private:
	
	std::list<Actor*> mActorList;
};