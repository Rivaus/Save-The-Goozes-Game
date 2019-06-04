#include "pch.h"
#include "Player.h"



Player::Player(float speed,int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset,
		std::string textureName, float positionX , float positionY ):
	Character(speed, pv, damage, world,boxWidth, boxWidth, boxOffset, textureName, positionX, positionY),
	interactiveShape(boxWidth/2)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(positionX + boxWidth, positionY);
	interactiveBody = world.CreateBody(&bodyDef);
	b2FixtureDef fixDef;
	b2CircleShape shape;
	shape.m_radius=  boxWidth / 2;
	fixDef.shape = &shape;
	fixDef.density = 0;
	fixDef.isSensor = true;
	interactiveBody->CreateFixture(&fixDef);
	interactiveBody->SetUserData(this);
	interactiveShape.setOrigin(boxWidth / 2, boxWidth / 2);
}

void Player::update(float deltaTime) {

	if (isDead) {
		pv = 3;
		isDead = false;
		body->SetTransform(b2Vec2{ .0f, .0f }, 0.0f);
		interactiveBody->SetTransform(b2Vec2{ 125.0f, .0f }, 0.0f);
	}

	InputManager* inputMng = InputManager::getInstance();

	b2Vec2 direction(inputMng->getAxis("Horizontal"), inputMng->getAxis("Vertical"));
	direction = Utils::normalize(direction);
	direction *= deltaTime * speed;
	body->SetLinearVelocity(direction);
	interactiveBody->SetLinearVelocity(direction);
	interactiveShape.setPosition(interactiveBody->GetPosition().x, interactiveBody->GetPosition().y);

	if (inputMng->isActionPressed(Action::Attack)) {
		isAttacking = true;
		std::cout << "J'attaque";
	}
	else
		isAttacking = false;

	Character::update(deltaTime);
}

void Player::draw(sf::RenderWindow& window) const {
	Character::draw(window);
	window.draw(interactiveShape);
}

