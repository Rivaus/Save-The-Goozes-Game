#pragma once
#include "Character.h"

class Player : Character
{
public:
	Player(float speed);
	~Player();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	float speed;
	sf::RectangleShape body;
};

