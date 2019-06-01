#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(float speed, int pv, b2World& world, std::string textureName);

private:
	sf::RectangleShape body;
};

