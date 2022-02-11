#pragma once

#include <SFML/Audio.hpp>
#include "Entity.h"
#include "tinyxml2.h"

// Bricks will have to be redone later with pointers
// The SoundBuffers and Textures of each brick type needs to be 
// in the level object, and then passed as a pointer to the bricks

enum BrickType { // NOT a class enum
    SOFT = 0,
    MEDIUM = 1,
    HARD = 2,
    IMPENETRABLE = 3,
    SIZE = 4
};

class Brick : public Entity {
public:
    Brick() : mIdentifier('\0'), mHitPoints(0), mBreakScore(0) {}
    void SetAttributes(const tinyxml2::XMLElement*);
    BrickType GetBrickType() const;
    inline bool IsDead() { return mHitPoints == 0 ? true : false; }
    inline unsigned int GetBreakScore() const{ return mBreakScore; }
    inline void DecreaseHitPoints() { mHitPoints--; }

    // QUESTIONABLE CHOICE
    inline sf::Texture GetTexture() const { return mTexture; }

private:
    char mIdentifier;
    unsigned int mHitPoints;
    /*sf::Sound mHitSound, mBreakSound;
    sf::SoundBuffer mHitSoundBuffer, mBreakSoundBuffer;*/
    unsigned int mBreakScore;
};

