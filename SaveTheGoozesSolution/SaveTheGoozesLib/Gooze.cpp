#include "pch.h"
#include "Gooze.h"


Gooze::Gooze(float speed, int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset,
	std::string textureName, GoozePower power, float positionX, float positionY) :
	Character(speed, pv, damage, world, boxWidth, boxWidth, boxOffset, textureName, positionX, positionY),
	_power(power)
{

}

void Gooze::update(float deltaTime) {
	if(isFound)
		body->SetTransform(b2Vec2_zero, 0);
}

GoozePower Gooze::getPower() {
	return _power;
}

void Gooze::found() {
	isFound = true;
}