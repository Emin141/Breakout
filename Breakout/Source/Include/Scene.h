#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Main.hpp>

#include "Actor.h"

class Scene {
public:
	virtual void load();
	virtual void draw();
private:
};