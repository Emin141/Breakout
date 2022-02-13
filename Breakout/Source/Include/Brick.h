#pragma once

#include <SFML/Audio.hpp>
#include "Entity.h"
#include "tinyxml2.h"

enum BrickType { // NOT a class enum
    SOFT = 0,
    MEDIUM = 1,
    HARD = 2,
    IMPENETRABLE = 3,
    SIZE = 4
};

class Brick : public Entity {
public:
    Brick() : 
        mIdentifier('\0'), mHitPoints(0) {}

    void SetAttributes(const tinyxml2::XMLElement*);
    BrickType GetBrickType() const;
    inline void SetTexture(const sf::Texture& texturePtr) { mShape.setTexture(&texturePtr); }
    inline bool IsDead() { return mHitPoints == 0 ? true : false; }
    inline void DecreaseHitPoints() { mHitPoints--; }

private:
    char mIdentifier;
    unsigned int mHitPoints;
};

