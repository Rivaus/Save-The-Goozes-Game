#pragma once
#include "Character.h"


enum class GoozePower {
	Invincible,
	Fast
};


class Gooze : public Character
{
public:
	Gooze(float speed, int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset,
		std::string textureName, GoozePower power, float positionX = 0.0f, float positionY = 0.0f);

	void update(float deltaTime) override;

	GoozePower getPower();

	void found();

private:
	GoozePower _power;
	bool isFound = false;
};

