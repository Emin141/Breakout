#pragma once

#include <SFML/Audio.hpp>
#ifdef V_DTOR_DEBUG
#include <plog/Log.h>
#endif

#include "Entity.h"
#include "tinyxml2.h"

// Seems redundant, but it makes the code more readable later
typedef char BrickID;

class Brick : public Entity {
public:
	Brick() 
		: mIdentifier('\0'), mHitPoints(0) {}
	Brick(const char id, const unsigned int hp) 
		: mIdentifier(id), mHitPoints(hp) {}
#ifdef V_DTOR_DEBUG
	virtual ~Brick() { PLOGD << "Brick Destroyed "; }
#else
	virtual ~Brick() {}
#endif

	inline void setID(const char id) { mIdentifier = id; }
	inline void setHP(const unsigned int hp) { mHitPoints = hp; }
	inline char getBrickID() const { return mIdentifier; }
	inline void setTexture(const sf::Texture& texture) { mShape.setTexture(&texture); }
	inline bool isDead() { return mHitPoints == 0 ? true : false; }
	inline void decreaseHitPoints() { mHitPoints--; }

private:
	BrickID mIdentifier;
	unsigned int mHitPoints;
};

