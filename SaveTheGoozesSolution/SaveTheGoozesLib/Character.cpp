#include "pch.h"
#include "Character.h"



Character::Character(float speed, int pv, b2World& world, int boxWidth, int boxHeight, int boxOffset, 
		std::string textureName, float positionX , float positionY) :
	speed(speed), pv(pv), sprite(), boxOffset(boxOffset)
{
	auto texture = AssetManager::getInstance()->getTexture(textureName);
	sprite.setTexture(*texture);
	sprite.setPosition(positionX, positionY);
	sprite.setOrigin(texture->getSize().x / 2, texture->getSize().x / 2);


	//Initialisation de la physique du character
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(positionX, positionY);
	body = world.CreateBody(&bodyDef);
	b2FixtureDef fixDef;
	b2PolygonShape shape;
	shape.SetAsBox(boxWidth / 2, boxHeight / 2);
	fixDef.shape = &shape;
	fixDef.density = 0;
	body->CreateFixture(&fixDef);
}

void Character::update(float deltaTime)
{
	auto directionX = body->GetLinearVelocity().x;
	if (directionX < 0 && !isFflipped) {
		sprite.setScale(sf::Vector2f{ -1.f, 1.f });
		isFflipped = true;
	}
	else if (directionX > 0 && isFflipped) {
		sprite.setScale(sf::Vector2f{ 1.f, 1.f });
		isFflipped = false;
	}
	sprite.setPosition(sf::Vector2f(body->GetPosition().x, body->GetPosition().y - boxOffset)); //ici le sprite suit le body
}

void Character::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

sf::Vector2f Character::getPosition()
{
	return sprite.getPosition();
}
