#pragma once

#include "Entity.h"
#include <SDL_audio.h>

enum class BrickType {
	SOFT = 0,
	MEDIUM,
	HARD,
	IMPENETRABLE
};

class Brick : Entity {
//	The brick class inherits Entity which has a CollisionBox
// 	and a ToBeRemoved flag. However, Entity inherits Actor,
// 	which is the class that has the dimensions, screen position
// 	image associated with the Brick, and ID to track which 
// 	brick it is (each entity has a unique ID). 
// 	
// 	The Actor grandparent also has the Load and Draw calls
// 	which mush be used by Entity. The Draw call can be inherited
// 	directly, however the Load call needs to be reimplemented
// 	as an overridden function
// 
public:
	
private:
	BrickType mBrickType;
	// Texture is implemented in parent as SDL_Surface*
	uint8_t mHitPoints;
	// SDL Audio Hit
	// SDL Audio break
	uint16_t mBreakScore;
};