#pragma once

#include <SFML/Audio.hpp>
#include "Entity.h"
#include "tinyxml2.h"

// Bricks will have to be redone later with pointers
// The SoundBuffers and Textures of each brick type needs to be 
// in the level object, and then passed as a pointer to the bricks

class Brick : public Entity {
public:
    Brick() : mIdentifier('\0'), mHitPoints(0), mBreakScore(0) {}
    void SetAttributes(const tinyxml2::XMLElement*);
    void PlayHitSound();
    void PlayBreakSound();
    bool operator==(const Brick&);
    bool operator!=(const Brick&);
    inline bool IsDead() { return mHitPoints == 0 ? true : false; }
    inline unsigned int GetBreakScore() const{ return mBreakScore; }
    inline void DecreaseHitPoints() { mHitPoints--; }

    // QUESTIONABLE CHOICE
    inline sf::Texture GetTexture() const { return mTexture; }

private:
    char mIdentifier;
    unsigned int mHitPoints;
    sf::Sound mHitSound, mBreakSound;
    sf::SoundBuffer mHitSoundBuffer, mBreakSoundBuffer;
    unsigned int mBreakScore;
};

