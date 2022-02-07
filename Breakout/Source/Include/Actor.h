#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Actor {
public:


/* UPON LOADING AN ACTOR, THE POSITION NEEDS TO BE GIVEN

							O	R

MAKE A METHOD THAT SETS THE POSITION

THE POSITION IS A POINT, BUT FOR ALL INTENTS AND PURPOSES
MAY BE CONSIDERED A VECTOR, BECAUSE WHAT ELSE IS A VECTOR?
*/

	Actor();
	~Actor();
	void Load(const std::string& assetPath, const sf::Vector2f& position);
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
	sf::Vector2f mPosition;
	sf::Vector2f mScale;
};