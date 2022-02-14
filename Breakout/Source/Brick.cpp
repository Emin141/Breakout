#include "Brick.h"

void Brick::setAttributes(const tinyxml2::XMLElement* brickTypeElement) {
	// Takes only the first character, hence the 0
	mIdentifier = brickTypeElement->Attribute("Id")[0];

	// Impenetrable bricks have different attributes
	if (mIdentifier == 'I') {
		mHitPoints = -1; // will automatically cast to a huge number 
		// because of integer promotion
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