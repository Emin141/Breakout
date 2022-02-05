#pragma once

// Entities are just actors with collision boxes
// However, new classes can be inherited from the entity class
// All three are special: 
// 
// Bricks can't move and have hitpoints
// The ball moves constantly
// The paddle moves on mouse control

#include "Actor.h"
#include "CollisionBox.h"

class Entity : Actor {
public:
	// Okay to have CollisionBox public because all of it's members are private
	CollisionBox mCollisionBox;

private:
};