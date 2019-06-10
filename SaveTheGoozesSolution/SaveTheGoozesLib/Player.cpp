#include "pch.h"
#include "Player.h"
#include "RaycastCallback.h"

Player::Player(float speed,int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset,
		std::string textureName, float positionX , float positionY ):
	Character(speed, pv, damage, world,boxWidth, boxWidth, boxOffset, textureName, positionX, positionY),
	world(world), line(sf::Vector2f(150.f, 5.f))
{
}

//permet de lier l'UI et le Player, pour la gestion des events "perdre une vie" et "meurt et ressucite"
void Player::addUI(UserInterface* ui) {
	_ui = ui;
}

/*
Initialise les mallus du perosnnage lorsque l'utilisateur a cliqué sur l'un des boutons
*/
void Player::setChoix(Choix choix) {
	switch (choix) {
	case Choix::Slide:
		isSliding = true;
		break;
	case Choix::Confus:
		isConfused = true;
		break;
	}

}

//met a jour les parametres du joueurs
void Player::update(float deltaTime) {

	if (isDead) {
		pv = 3;
		isDead = false;
		body->SetTransform(b2Vec2{ .0f, .0f }, 0.0f);
	}

	handleInput(deltaTime);

	Character::update(deltaTime);
	line.setPosition(body->GetPosition().x + 100.f, body->GetPosition().y);
}

//gere les deplacements du joueur quand on appuie sur les fleches du clavier
void Player::handleInput(float deltaTime) {
	float directionX = 0;
	float directionY = 0;

	//Horizontal movment
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
		|| sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 50) {
		directionX = 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)
		|| sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < -50) {
		directionX = -1.0;
	}
	//Vertical movment
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)
		|| sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) < -50) {
		directionY = -1.0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
		|| sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) > 50) {
		directionY = 1.0;
	}
	if (directionX != .0f || directionY != .0f) {
		move(directionX, directionY, deltaTime);
	}
	else if (!isSliding)
		body->SetLinearVelocity(b2Vec2_zero);

	//Actions
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0, 2)) {
		attack();
	}
}

//deplace le joueur dans le monde
void Player::move(float movX, float movY, float deltaTime) {
	b2Vec2 direction{ movX, movY };
	if (isConfused) {
		direction.x = -movY;
		direction.y = -movX;
	}
	direction = Utils::normalize(direction);
	direction *= deltaTime * speed;
	body->SetLinearVelocity(direction);
}

//gere l'attaque du joueur
void Player::attack() {
	b2Vec2 startPointForward { body->GetPosition().x + 100.f, body->GetPosition().y };
	b2Vec2 endPointForward { body->GetPosition().x + 250.f, body->GetPosition().y };

	b2Vec2 startPointBehind{ body->GetPosition().x - 100.f, body->GetPosition().y };
	b2Vec2 endPointBehind{ body->GetPosition().x - 250.f, body->GetPosition().y };

	RaycastCallback callback(this);
	world.RayCast(&callback, startPointForward, endPointForward);
	world.RayCast(&callback, startPointBehind, endPointBehind);
}

//gere l'affichage du joueur
void Player::draw(sf::RenderWindow& window) const {
	Character::draw(window);
	window.draw(line);
}

//gere quand le joueur se prend des degats et notifie l'UI
void Player::takeDamage(int damage) {
	if (!isInvincible) {
		if (Character::takeDamage(damage)) {
			if (isDead) {
				_ui->onNotify(Events::PlayerDied); //on remet tout les coeurs dans l'UI
			}
			else {
				_ui->onNotify(Events::PlayerTakeDamage); //on perd un coeur dans l'ui	
			}
		}
	}
}

//gere quand le joueur attrape une oie
void Player::findGooze(GoozePower power) {
	switch (power) {
	case GoozePower::Invincible:
		isInvincible = true;
		scale = 1.3f;
		std::cout << "Je deviens invincible !" << std::endl;
		sprite.setScale(sf::Vector2f{ scale, scale });
		break;
	}
}