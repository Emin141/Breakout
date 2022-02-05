#include "CollisionBox.h"

#include <cmath>

bool CollisionBox::CheckCollision(const CollisionBox& otherCollisionBox) const {
	uint16_t verticalDistance = abs(mCenter.y - otherCollisionBox.GetCenter().y);
	uint16_t horizontalDistance = abs(mCenter.x - otherCollisionBox.GetCenter().x);

	if (verticalDistance <= (mWidth + otherCollisionBox.GetWidth()) / 2	&&
		horizontalDistance <= (mHeight + otherCollisionBox.GetHeight()) / 2)
		return true;
	return false;
}