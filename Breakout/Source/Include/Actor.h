#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Actor {
public:
	Actor();
	~Actor();
	void Load(const std::string& assetPath);
	void Draw(sf::RenderWindow& window);
	inline uint8_t GetID() const { return mID; }
	
	static void IncreaseActorCount();
	static void DecreaseActorCount();
	
	inline bool operator == (const Actor& s) const { return mID == s.mID; }
	inline bool operator != (const Actor& s) const { return !operator==(s); }
private:
	static uint8_t ActorCount;
	uint8_t mID;
	sf::Texture mTexture;
	sf::Sprite mSprite;
	uint16_t mXPos, mYPos;
	uint16_t mWidth, mHeight;
};