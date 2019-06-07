#pragma once
#include "Character.h"
#include"Gooze.h"
#include "UserInterface.h"

#include <thread>

enum class Choix {
	Slide,
	Confus
};

class Player : public Character
{
public:
	Player(float speed, int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset, 
		std::string textureName="Alfonso", float positionX = 0, float positionY = 0);

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) const override;

	void addUI(UserInterface* ui);
	void setChoix(Choix choix);
	void takeDamage(int damage);

	void attack();

	void findGooze(GoozePower power);

private :
	void handleInput(float deltaTime);
	void move(float moX, float movY, float deltaTime);

private :
	bool isAttacking = false;
	b2World& world;
	sf::RectangleShape line;
	UserInterface* _ui;
	bool isConfused = false;
	bool isSliding = false;
	bool isInvincible = false;
};

