#include "pch.h"
#include "Player.h"



Player::Player(float speed,int pv,  b2World& world, std::string textureName, float positionX , float positionY ):
	Character(speed, pv,  world, textureName, positionX, positionY)
{
}

void Player::update(float deltaTime) {
	InputManager* inputMng = InputManager::getInstance();
	b2Vec2 direction(inputMng->getAxis("Horizontal"), inputMng->getAxis("Vertical"));
	direction = Utils::normalize(direction);
	direction *= deltaTime * speed;
	//std::cout << "vitesse = " << speed << std::endl;
	body->SetLinearVelocity(direction);
	Character::update(deltaTime);
}



