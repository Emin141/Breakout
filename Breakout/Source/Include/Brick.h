#pragma once

#include <SFML/Audio.hpp>
#include "Entity.h"
#include "tinyxml2.h"

// Bricks will have to be redone later with pointers
// The SoundBuffers and Textures of each brick type needs to be 
// in the level object, and then passed as a pointer to the bricks

class Brick : Entity {
public:
    void setAttributes(const tinyxml2::XMLElement* brickTypeElement);

    void playHitSound();
    //void playBreakSound();
    inline bool isDead() { return mHitPoints == 0 ? true : false; }
    inline void debugPrint() const { std::cout << mHitPoints; }
private:
    char* mIdentifier;
    sf::Texture mTexture;
    unsigned int mHitPoints;
    sf::Sound mHitSound, mBreakSound;
    sf::SoundBuffer mHitSoundBuffer, mBreakSoundBuffer;
    unsigned int mBreakScore;
};

