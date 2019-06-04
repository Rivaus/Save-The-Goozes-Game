#pragma once
#include "Character.h"
#include <vector>

class Ennemy : public Character
{
public:
	Ennemy (float speed, int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset,
		std::string textureName ="Alfonso", float positionX = 0, float positionY = 0 );

	void update(float deltaTime) override;

	void addWaypoint(sf::Vector2f const& waypoint);

	void takeDamage(int damage) override;
private:
	std::vector<sf::Vector2f> waypoints;
	int indexWaypoint;
};

