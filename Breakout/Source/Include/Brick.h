#pragma once

#include <SFML/Audio.hpp>
#ifdef V_DTOR_DEBUG
#include <plog/Log.h>
#endif

#include "Entity.h"
#include "tinyxml2.h"

enum BrickType { // NOT a class enum !
	SOFT = 0,
	MEDIUM = 1,
	HARD = 2,
	IMPENETRABLE = 3,
	SIZE = 4
};

class Brick : public Entity {
public:
	Brick() : mIdentifier('\0'), mHitPoints(0) {}
#ifdef V_DTOR_DEBUG
	virtual ~Brick() { PLOGD << "Brick Destroyed "; }
#else
	virtual ~Brick() {}
#endif

	void setAttributes(const tinyxml2::XMLElement*);
	BrickType getBrickType() const;
	inline void setTexture(const sf::Texture& texture) { mShape.setTexture(&texture); }
	inline bool isDead() { return mHitPoints == 0 ? true : false; }
	inline void decreaseHitPoints() { mHitPoints--; }

private:
	char mIdentifier;
	unsigned int mHitPoints;
};

