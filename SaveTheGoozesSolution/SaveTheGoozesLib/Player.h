#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(float speed, int pv, b2World& world);

private:
	sf::RectangleShape body;
};

