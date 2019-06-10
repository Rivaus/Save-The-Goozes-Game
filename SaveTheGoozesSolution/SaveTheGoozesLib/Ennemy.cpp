#include "pch.h"
#include "Ennemy.h"


Ennemy::Ennemy(float speed, int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset,
	std::string textureName , float positionX, float positionY) :
	Character(speed,pv, damage, world, boxWidth, boxHeight, boxOffset, textureName,positionX,positionY),
	waypoints()
{
	indexWaypoint = 0;
}

/*
Ajoute un lieu de passage dans la ronde de l'ennemi.
*/
void Ennemy::addWaypoint(sf::Vector2f const& waypoint) {
	waypoints.push_back(waypoint);
}


void Ennemy::update(float deltaTime) {

	if (isDead) {
		body->SetTransform(b2Vec2{ .0f, .0f }, 0);
	}
	//si on atteint le point visé
	if (Utils::absoluteDistance(body->GetPosition(), waypoints[indexWaypoint]) < 5) {
		indexWaypoint++;
		if (indexWaypoint >= waypoints.size()) {
			indexWaypoint = 0;
		}
	}
	b2Vec2 direction(waypoints[indexWaypoint].x - body->GetPosition().x, waypoints[indexWaypoint].y - body->GetPosition().y );
	direction = Utils::normalize(direction);
	direction *= deltaTime * speed;
	body->SetLinearVelocity(direction);
	
	Character::update(deltaTime);

}
