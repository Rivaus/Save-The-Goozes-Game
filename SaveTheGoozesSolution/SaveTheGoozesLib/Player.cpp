#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "Utils.h"


Player::Player(float speed,int pv):
	Character(speed, pv)
{
	body.setSize(sf::Vector2f(100.0f, 100.0f));
	body.setPosition(200.0f, 200.0f);
	body.setFillColor(sf::Color::Green);
}


void Player::update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	InputManager* input = InputManager::getInstance();

	sf::Vector2f direction{ input->getAxis("Horizontal"), input->getAxis("Vertical") };
	movement = Utils::normalize(direction);

	body.move(movement);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(body);
}
