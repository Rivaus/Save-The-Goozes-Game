#pragma once
#include "Character.h"

#include <thread>

class Player : public Character
{
public:
	Player(float speed, int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset, 
		std::string textureName="Alfonso", float positionX = 0, float positionY = 0);

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) const override;

	void attack();

private :
	bool isAttacking = false;
	b2World& world;
	sf::RectangleShape line;
};

