#include "Entity.h"

Entity::Entity(){}

bool Entity::CollidedWith(const Entity& otherEntity) const {
	// Axis aligned bounding boxes algorithm
	// aka, AABB


#define COLLISION_V 2
#if COLLISION_V == 1
	if (
		// X Axis
		(
			mPosition.x > otherEntity.GetPosition().x &&
			((mPosition.x + mSize.x) < (otherEntity.GetPosition().x + otherEntity.GetSize().x))
			)
		&&
		// Y Axis
		(
			(mPosition.y + mSize.y ) > otherEntity.GetPosition().y &&
			((mPosition.y +mSize.y ) < (otherEntity.GetPosition().y + otherEntity.GetSize().y))
			)
		) 
		return true;
#elif COLLISION_V == 2

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

	return (xCondition && yCondition);
#endif
}

bool Entity::operator==(const Entity& otherEntity) const {
	return mPosition == otherEntity.GetPosition();
}

bool Entity::operator!=(const Entity& otherEntity) const {
	return !(*this == otherEntity);
}