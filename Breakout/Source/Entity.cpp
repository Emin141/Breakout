#include "Entity.h"

bool Entity::CollidedWith(const Entity& otherEntity, CollisionSide& collisionSide) const{
	// Axis aligned bounding boxes algorithm
	// aka, AABB
	
	bool xCondition;
	xCondition = (
		!((mPosition.x + mSize.x) < otherEntity.GetPosition().x))
		&&
		!(mPosition.x > (otherEntity.GetPosition().x + otherEntity.GetSize().x)
			);

	bool yCondition;
	yCondition = (
		!((mPosition.y + mSize.y) < otherEntity.GetPosition().y))
		&&
		!(mPosition.y > (otherEntity.GetPosition().y + otherEntity.GetSize().y)
			);

	bool collided = xCondition && yCondition;

	if (collided) {
		if (mPreviousPosition.x + mSize.x < otherEntity.GetPosition().x &&
			mPosition.x + mSize.x >= otherEntity.GetPosition().x)
			collisionSide = CollisionSide::LEFT;
		if (mPreviousPosition.x >= otherEntity.GetPosition().x+otherEntity.GetSize().x &&
			mPosition.x < otherEntity.GetPosition().x +otherEntity.GetSize().x)
			collisionSide = CollisionSide::RIGHT;
		if (mPreviousPosition.y + mSize.y < otherEntity.GetPosition().y &&
			mPosition.y + mSize.y >= otherEntity.GetPosition().y)
			collisionSide = CollisionSide::TOP;
		if (mPreviousPosition.y >= otherEntity.GetPosition().y + otherEntity.GetSize().y &&
			mPosition.y < otherEntity.GetPosition().y + otherEntity.GetSize().y)
			collisionSide = CollisionSide::BOTTOM;
	}

	return collided;
}

bool Entity::operator==(const Entity& otherEntity) const {
	return mPosition == otherEntity.GetPosition();
}

bool Entity::operator!=(const Entity& otherEntity) const {
	return !(*this == otherEntity);
}