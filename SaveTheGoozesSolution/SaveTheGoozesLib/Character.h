#pragma once

#include<SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Utils.h"
#include "AssetManager.h"
#include <string>

class Character
{

public:
	Character(float speed, int pv, b2World& world,std::string textureName, float positionX = 0, float positionY = 0);
	virtual ~Character() = default ;
	
	sf::Vector2f getPosition();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);


private:
	int pv;
	float speed;
	b2Body* body;
	sf::Sprite sprite;
	sf::RectangleShape shape;
	
};

