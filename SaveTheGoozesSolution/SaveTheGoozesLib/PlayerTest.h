#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "InputManager.h"
#include "Utils.h"
#include "AssetManager.h"


class PlayerTest
{
public:
	PlayerTest(b2World& world) :
		shape(sf::Vector2f(100, 100)),
		sprite()
		{
		shape.setFillColor(sf::Color::Red);
		shape.setPosition(sf::Vector2f(0, 0));
		shape.setOrigin(50, 50);

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
		b2PolygonShape shape;
		shape.SetAsBox(texture->getSize().x / 2, texture->getSize().x / 2);
		fixDef.shape = &shape;
		fixDef.density = 0;
		body->CreateFixture(&fixDef);
	}

	void update(float deltaTime) {
		InputManager* inputMng = InputManager::getInstance();
		b2Vec2 direction(inputMng->getAxis("Horizontal"), inputMng->getAxis("Vertical"));
		direction *= deltaTime * 100.0f;
		body->SetLinearVelocity(direction);
		//body->ApplyForce(direction, b2Vec2(0, 0), true);
		//body->SetTransform(b2Vec2(body->GetPosition().x + direction.x, body->GetPosition().y + direction.y), 0);
		std::cout << "Body : " << body->GetPosition().x << "; " << body->GetPosition().y << std::endl;

		shape.setPosition(sf::Vector2f(body->GetPosition().x, body->GetPosition().y));
		sprite.setPosition(sf::Vector2f(body->GetPosition().x, body->GetPosition().y));
	}

	void draw(sf::RenderWindow& window) {
		window.draw(shape);
		window.draw(sprite);
	}

	sf::Vector2f getPosition() {
		return shape.getPosition();
	}

private:
	sf::RectangleShape shape;
	b2Body* body;
	sf::Sprite sprite;
};

