#include "Brick.h"

void Brick::setAttributes(const tinyxml2::XMLElement* brickTypeElement) {
    mIdentifier = 0[const_cast<char*>(brickTypeElement->Attribute("Id"))];
    
    // Impenetrable bricks have different attributes
    if (mIdentifier == 'I') {
        mHitPoints = -1; // will automatically cast to a huge number
    }
    else {
        mHitPoints = strtod(brickTypeElement->Attribute("HitPoints"), NULL);
    }
}

BrickType Brick::getBrickType() const {
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