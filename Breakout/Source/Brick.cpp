#include "Brick.h"
#include "plog/Log.h"

void Brick::setAttributes(const tinyxml2::XMLElement* brickTypeElement) {
	// Takes only the first character, hence the 0

	try {
		if (brickTypeElement->Attribute("Id") == nullptr)
			throw "Cannot read attribute Id";

		mIdentifier = brickTypeElement->Attribute("Id")[0];

		if (mIdentifier == 'I') {
			mHitPoints = -1; // will automatically cast to a huge number 
			// because of integer promotion
		}
		else {
			if (brickTypeElement->Attribute("HitPoints") == nullptr)
				throw "Cannot read attribute HitPoints";
			mHitPoints = strtod(brickTypeElement->Attribute("HitPoints"), NULL);
		}
	}
	catch (std::string message) {
		PLOGD << message;
		exit(-1);
	}

	// Impenetrable bricks have different attributes
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