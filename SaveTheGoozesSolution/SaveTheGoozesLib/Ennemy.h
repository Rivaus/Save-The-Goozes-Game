#pragma once
#include "Character.h"
class Ennemy : public Character
{
public:
	Ennemy(int pv, float speed, b2World& world, std::vector<sf::Vector2f> waypoints, std::string textureName ="Alfonso",
		float positionX = 0, float positionY = 0 );

	void update(float deltaTime) override;
private:
	std::vector<sf::Vector2f> waypoints;
	int indexWaypoint;
};

