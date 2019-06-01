#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(float speed, int pv); 
	~Player();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape body;
};

