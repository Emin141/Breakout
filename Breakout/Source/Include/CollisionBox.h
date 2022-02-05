#pragma once

#include <iostream>
#include "Point.h"

class CollisionBox {
public:
	CollisionBox(Point center, uint16_t width, uint16_t height)
		: mCenter(center), mWidth(width), mHeight(height) {}

	inline Point GetCenter() const { return mCenter; }
	inline uint16_t GetWidth() const { return mWidth; }
	inline uint16_t GetHeight() const { return mHeight; }
	bool CheckCollision(const CollisionBox& otherCollisionBox) const;
private:
	Point mCenter;
	uint16_t mWidth, mHeight;
};