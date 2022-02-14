#include "Entity.h"

bool Entity::collidedWith(const Entity& otherEntity, CollisionSide& collisionSide) const {
	// Axis aligned bounding boxes algorithm
	// aka, AABB

	bool xCondition;
	xCondition = (
		!((mPosition.x + mSize.x) < otherEntity.getPosition().x))
		&&
		!(mPosition.x > (otherEntity.getPosition().x + otherEntity.getSize().x)
			);

	bool yCondition;
	yCondition = (
		!((mPosition.y + mSize.y) < otherEntity.getPosition().y))
		&&
		!(mPosition.y > (otherEntity.getPosition().y + otherEntity.getSize().y)
			);

	bool collided = xCondition && yCondition;

	// If the collision happened, checks the direction of the collision
	if (collided) {
		if (mPreviousPosition.x + mSize.x < otherEntity.getPosition().x &&
			mPosition.x + mSize.x >= otherEntity.getPosition().x)
			collisionSide = CollisionSide::LEFT;
		if (mPreviousPosition.x >= otherEntity.getPosition().x + otherEntity.getSize().x &&
			mPosition.x < otherEntity.getPosition().x + otherEntity.getSize().x)
			collisionSide = CollisionSide::RIGHT;
		if (mPreviousPosition.y + mSize.y < otherEntity.getPosition().y &&
			mPosition.y + mSize.y >= otherEntity.getPosition().y)
			collisionSide = CollisionSide::TOP;
		if (mPreviousPosition.y >= otherEntity.getPosition().y + otherEntity.getSize().y &&
			mPosition.y < otherEntity.getPosition().y + otherEntity.getSize().y)
			collisionSide = CollisionSide::BOTTOM;
	}

	return collided;
}

bool Entity::operator==(const Entity& otherEntity) const {
	return mPosition == otherEntity.getPosition();
}

bool Entity::operator!=(const Entity& otherEntity) const {
	return !(*this == otherEntity);
}