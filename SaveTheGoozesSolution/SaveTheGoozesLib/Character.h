#pragma once
#ifndef CHARACTER_DEF
#define CHARACTER_DEF


#include<SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Utils.h"
#include "AssetManager.h"
#include <string>
#include <thread>

class Character
{

public:
	Character(float speed, int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset, 
		std::string textureName, float positionX = 0, float positionY = 0);
	virtual ~Character() = default ;
	
	
	virtual void update(float deltaTime);
	virtual void draw(sf::RenderWindow& window) const;
	

	sf::Vector2f getPosition();
	int getDamage();
	bool takeDamage(int damage);
	static void waitForBeingHit(Character* player, int waitingTime);

	bool dead();
	int getPv();

private:
	int damage;
	sf::RectangleShape shape;
	int boxOffset;
	bool canBeHit = true;
	std::vector<sf::Texture*> textures;
	
protected:
	sf::Sprite sprite;
	b2Body* body;
	int pv;
	float speed;
	bool isFlipped = false;
	bool isDead = false;
	float scale = 1.0f;
};

#endif // !CHARACTER_DEF