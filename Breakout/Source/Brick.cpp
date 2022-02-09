#include "Brick.h"

void Brick::SetAttributes(const tinyxml2::XMLElement* brickTypeElement) {
    mIdentifier = 0[const_cast<char*>(brickTypeElement->Attribute("Id"))];
    mTexture.loadFromFile("Resource/" + std::string(brickTypeElement->Attribute("Texture")));
    mHitSoundBuffer.loadFromFile("Resource/" + std::string(brickTypeElement->Attribute("HitSound")));
    
    // Impenetrable bricks have different attributes
    if (mIdentifier == 'I') {
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

    mShape.setTexture(&mTexture);
}

void Brick::PlayHitSound() {
    mHitSound.play();
}

void Brick::PlayBreakSound() {
    mBreakSound.play();
}

bool Brick::operator==(const Brick& otherBrick) {
    return (mPosition == otherBrick.GetPosition());
}

bool Brick::operator!=(const Brick& otherBrick) {
    return !(*this == otherBrick);
}