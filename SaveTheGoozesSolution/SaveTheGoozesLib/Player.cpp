#include "pch.h"
#include "Player.h"
#include "RaycastCallback.h"

Player::Player(float speed,int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset,
		std::string textureName, float positionX , float positionY ):
	Character(speed, pv, damage, world,boxWidth, boxWidth, boxOffset, textureName, positionX, positionY),
	world(world), line(sf::Vector2f(150.f, 5.f))
{
}

void Player::addUI(UserInterface* ui) {
	_ui = ui;
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

	if (inputMng->isActionPressed(Action::Attack)) {
		attack();
	}
	Character::update(deltaTime);
	line.setPosition(body->GetPosition().x + 100.f, body->GetPosition().y);
}

void Player::attack() {
	b2Vec2 startPointForward { body->GetPosition().x + 100.f, body->GetPosition().y };
	b2Vec2 endPointForward { body->GetPosition().x + 250.f, body->GetPosition().y };

	b2Vec2 startPointBehind{ body->GetPosition().x - 100.f, body->GetPosition().y };
	b2Vec2 endPointBehind{ body->GetPosition().x - 250.f, body->GetPosition().y };

	RaycastCallback callback(this);
	world.RayCast(&callback, startPointForward, endPointForward);
	world.RayCast(&callback, startPointBehind, endPointBehind);
}

void Player::draw(sf::RenderWindow& window) const {
	Character::draw(window);
	window.draw(line);
}

void Player::takeDamage(int damage) {
	Character::takeDamage(damage);
	if (isDead) {
		_ui->onNotify(Events::PlayerDied); //on remet tout les coeurs dans l'UI
	}
	else {
		_ui->onNotify(Events::PlayerTakeDamage); //on perd un coeur dans l'ui
	}
	
}