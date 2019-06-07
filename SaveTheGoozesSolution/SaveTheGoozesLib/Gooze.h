#pragma once
#include "Character.h"

class Gooze : public Character
{
public:
	Gooze(float speed, int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset,
		std::string textureName, float positionX = 0.0f, float positionY = 0.0f);
};

