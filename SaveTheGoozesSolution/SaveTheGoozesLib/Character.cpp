#include "pch.h"
#include "Character.h"
#include "InputManager.h"


Character::Character(float speed, int pv, b2World& world) : 
	speed(speed), pv(pv), sprite()
{
	auto texture = AssetManager::getInstance()->getTexture("Alfonso");
	sprite.setTexture(*texture);
	sprite.setPosition(0, 0);
	sprite.setOrigin(texture->getSize().x / 2, texture->getSize().x / 2);


	//Initialisation de la physique du player
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0, 0);
	body = world.CreateBody(&bodyDef);
	b2FixtureDef fixDef;
	fixDef.density = 0;
	body->CreateFixture(&fixDef);
}

void Character::update(float deltaTime)
{
	InputManager* inputMng = InputManager::getInstance();
	b2Vec2 direction(inputMng->getAxis("Horizontal"), inputMng->getAxis("Vertical"));
	direction *= deltaTime * 100.0f;
	body->SetLinearVelocity(direction);

	sprite.setPosition(sf::Vector2f(body->GetPosition().x, body->GetPosition().y)); //ici le sprite suit le body
}

void Character::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
