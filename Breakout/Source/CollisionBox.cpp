#include "CollisionBox.h"

#include <cmath>

bool CollisionBox::CheckCollision(const CollisionBox& otherCollisionBox) const {
	float verticalDistance = fabsf(mCenter.y - otherCollisionBox.GetCenter().y);
	float horizontalDistance = fabsf(mCenter.x - otherCollisionBox.GetCenter().x);

	if (verticalDistance <= (mSize.x + otherCollisionBox.GetWidth()) / 2	&&
		horizontalDistance <= (mSize.y + otherCollisionBox.GetHeight()) / 2)
		return true;
	return false;
}

void CollisionBox::CreateCollisionBox(const sf::Vector2i& center, const sf::Vector2f& size) {
	mCenter = center;
	mSize = size;
}