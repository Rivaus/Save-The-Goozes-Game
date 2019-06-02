#include "pch.h"
#include "Ennemy.h"


Ennemy::Ennemy(int pv, float speed, b2World& world, std::vector<sf::Vector2f> waypoints, 
	std::string textureName , float positionX, float positionY) :
	Character(pv, speed, world,textureName,positionX,positionY),
	waypoints(waypoints)
{
	waypoint = waypoints[0];
}


void Ennemy::update(float deltaTime) {

	
	b2Vec2 direction(waypoint.x - body->GetPosition().x, waypoint.y - body->GetPosition().y );
	direction = Utils::normalize(direction);
	direction *= deltaTime * speed;
	body->SetLinearVelocity(direction);
	
	
	Character::update(deltaTime);

}

