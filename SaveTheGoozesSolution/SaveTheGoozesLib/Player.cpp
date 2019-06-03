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

void Player::takeDamage(int damage){
	if (canBeHit) {
		canBeHit = false;
		auto t = std::thread(Player::waitForBeingHit, this, 2);
		t.detach();
		Character::takeDamage(damage);
		std::cout << "Je suis touché, je n'ai plus que " << pv << " pv." << std::endl;
		if (pv <= 0) {
			std::cout << "Je suis mort. RIP." << pv << " pv." << std::endl;
			isDead = true;
		}
	}
}

void Player::waitForBeingHit(Player* player, int waitingTime) {
	std::this_thread::sleep_for(std::chrono::seconds(waitingTime));
	player->canBeHit = true;
	std::cout << "Je peux etre à nouveau touché." << std::endl;
}
