#pragma once

#include<SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Utils.h"
#include "AssetManager.h"
#include <string>

class Character
{

public:
	Character(float speed, int pv, b2World& world,std::string textureName );

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	int pv;
	float speed;
	b2Body* body;
	sf::Sprite sprite;
	
};

