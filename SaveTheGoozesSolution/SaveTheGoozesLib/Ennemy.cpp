#include "pch.h"
#include "Ennemy.h"


Ennemy::Ennemy(int pv, float speed, b2World& world, int boxWidth, int boxHeight, int boxOffset,
	std::string textureName , float positionX, float positionY) :
	Character(pv, speed, world, boxWidth, boxHeight, boxOffset, textureName,positionX,positionY),
	waypoints()
{
	indexWaypoint = 0;
}

void Ennemy::addWaypoint(sf::Vector2f const& waypoint) {
	waypoints.push_back(waypoint);
}


void Ennemy::update(float deltaTime) {

	if (Utils::absoluteDistance(body->GetPosition(), waypoints[indexWaypoint]) < 5) {
		indexWaypoint++;
		if (indexWaypoint >= waypoints.size()) {
			indexWaypoint = 0;
		}
		std::cout << "je suis arrivé et je cherche maintenant " << indexWaypoint << std::endl;
	}
	b2Vec2 direction(waypoints[indexWaypoint].x - body->GetPosition().x, waypoints[indexWaypoint].y - body->GetPosition().y );
	std::cout << "Vitesse " << body->GetLinearVelocity().x << " ;" << body->GetLinearVelocity().y << std::endl;
	direction = Utils::normalize(direction);
	direction *= deltaTime * speed;
	body->SetLinearVelocity(direction);
	
	Character::update(deltaTime);

}

