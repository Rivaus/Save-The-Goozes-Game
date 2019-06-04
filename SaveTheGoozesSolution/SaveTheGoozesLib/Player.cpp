#include "pch.h"
#include "Player.h"



Player::Player(float speed,int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset,
		std::string textureName, float positionX , float positionY ):
	Character(speed, pv, damage, world,boxWidth, boxWidth, boxOffset, textureName, positionX, positionY)
{
}

void Player::update(float deltaTime) {

	if (isDead) {
		pv = 3;
		isDead = false;
		body->SetTransform(b2Vec2{ .0f, .0f }, 0.0f);
	}

	InputManager* inputMng = InputManager::getInstance();

	b2Vec2 direction(inputMng->getAxis("Horizontal"), inputMng->getAxis("Vertical"));
	direction = Utils::normalize(direction);
	direction *= deltaTime * speed;
	body->SetLinearVelocity(direction);

	Character::update(deltaTime);
}



