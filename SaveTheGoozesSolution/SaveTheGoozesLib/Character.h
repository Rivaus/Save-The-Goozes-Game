#pragma once

#include<SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Utils.h"
#include "AssetManager.h"
#include <string>
#include "InputManager.h"
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
	void takeDamage(int damage);
	static void waitForBeingHit(Character* player, int waitingTime);

private:
	int damage;
	sf::Sprite sprite;
	sf::RectangleShape shape;
	int boxOffset;
	bool canBeHit = true;
	std::vector<sf::Texture*> textures;
	
protected:
	b2Body* body;
	int pv;
	float speed;
	bool isFlipped = false;
	bool isDead = false;
};

