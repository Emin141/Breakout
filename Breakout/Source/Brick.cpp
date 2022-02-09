#include "Brick.h"

void Brick::setAttributes(const tinyxml2::XMLElement* brickTypeElement) {
    mIdentifier = const_cast<char*>(brickTypeElement->Attribute("Id"));
    mTexture.loadFromFile("Resource/" + std::string(brickTypeElement->Attribute("Texture")));
    std::cout << "Resource/" + std::string(brickTypeElement->Attribute("HitSound")) << "\n";
    mHitSoundBuffer.loadFromFile("Resource/" + std::string(brickTypeElement->Attribute("HitSound")));
    if (mIdentifier[0] == 'I') {
        mHitPoints = -1; // will automatically cast to a huge number
        // mBreakSound will default
        mBreakScore = 0;
    }
    else {
        mHitPoints = strtod(brickTypeElement->Attribute("HitPoints"), NULL);
        mBreakSoundBuffer.loadFromFile("Resource/" + std::string(brickTypeElement->Attribute("BreakSound")));
        mBreakScore = strtod(brickTypeElement->Attribute("BreakScore"), NULL);
    }

    mHitSound.setBuffer(mHitSoundBuffer);
    mBreakSound.setBuffer(mBreakSoundBuffer);
}

void Brick::playHitSound() {
   /* sf::Sound sound;
    sound.setBuffer(mHitSound);
    sound.play();*/
    mHitSound.play();
}