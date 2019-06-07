#include "pch.h"
#include "Gooze.h"


Gooze::Gooze(float speed, int pv, int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset,
	std::string textureName, float positionX, float positionY) :
	Character(speed, pv, damage, world, boxWidth, boxWidth, boxOffset, textureName, positionX, positionY)
{

}


