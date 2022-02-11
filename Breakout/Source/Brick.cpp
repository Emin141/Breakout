#include "Brick.h"

void Brick::SetAttributes(const tinyxml2::XMLElement* brickTypeElement) {
    mIdentifier = 0[const_cast<char*>(brickTypeElement->Attribute("Id"))];
    mTexture.loadFromFile("Resource/" + std::string(brickTypeElement->Attribute("Texture")));
    
    // Impenetrable bricks have different attributes
    if (mIdentifier == 'I') {
        mHitPoints = -1; // will automatically cast to a huge number
        mBreakScore = 0;
    }
    else {
        mHitPoints = strtod(brickTypeElement->Attribute("HitPoints"), NULL);
        mBreakScore = strtod(brickTypeElement->Attribute("BreakScore"), NULL);
    }

    mShape.setTexture(&mTexture);
}

BrickType Brick::GetBrickType() const {
    switch (mIdentifier) {
    case 'S':
        return SOFT;
        break;
    case 'M':
        return MEDIUM;
        break;
    case 'H':
        return HARD;
        break;
    default:
        return IMPENETRABLE;
        break;
    }
}