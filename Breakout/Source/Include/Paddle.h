#pragma once

#ifdef V_DTOR_DEBUG
#include <plog/Log.h>
#endif

#include "Entity.h"

class Paddle : public Entity {
public:
	Paddle() {}
#ifdef V_DTOR_DEBUG
	virtual ~Paddle() { PLOGD << "Paddle destroyed "; }
#else
	virtual ~Paddle() {}
#endif

	void setTexture(const sf::Texture texture);
	void setPosition(const sf::Vector2i& position, const sf::RenderWindow& window);

private:
	sf::Texture mTexture;
};