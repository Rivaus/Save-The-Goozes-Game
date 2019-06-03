#pragma once
#include "Character.h"

#include <thread>

class Player : public Character
{
public:
	Player(float speed, int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset, 
		std::string textureName="Alfonso", float positionX = 0, float positionY = 0);
	void update(float deltaTime) override;

	void takeDamage(int damage) override;

	static void waitForBeingHit(Player* player, int waitingTime);

private:
	bool canBeHit = true;
};

