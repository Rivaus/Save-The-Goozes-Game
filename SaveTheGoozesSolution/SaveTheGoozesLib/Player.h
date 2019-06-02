#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(float speed, int pv, b2World& world, int boxWidth, int boxHeight, int boxOffset, 
		std::string textureName="Alfonso", float positionX = 0, float positionY = 0);
	void update(float deltaTime) override;

};

