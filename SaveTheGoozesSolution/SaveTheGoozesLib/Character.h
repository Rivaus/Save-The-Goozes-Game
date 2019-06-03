#pragma once

#include<SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Utils.h"
#include "AssetManager.h"
#include <string>
#include "InputManager.h"

class Character
{

public:
	Character(float speed, int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset, 
		std::string textureName, float positionX = 0, float positionY = 0);
	virtual ~Character() = default ;
	
	
	virtual void update(float deltaTime);
	void draw(sf::RenderWindow& window) const;
	

	sf::Vector2f getPosition();
	int getDamage();
	virtual void takeDamage(int damage);

private:
	int damage;
	sf::Sprite sprite;
	sf::RectangleShape shape;
	int boxOffset;
	
protected:
	b2Body* body;
	int pv;
	float speed;
	bool isFflipped = false;
	bool isDead = false;
};

