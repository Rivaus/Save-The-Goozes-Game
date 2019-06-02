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
	Character(float speed, int pv, b2World& world,std::string textureName, float positionX = 0, float positionY = 0);
	virtual ~Character() = default ;
	
	sf::Vector2f getPosition();
	virtual void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	float speed;

private:
	int pv;
	sf::Sprite sprite;
	sf::RectangleShape shape;
protected:
	b2Body* body;
	
};

