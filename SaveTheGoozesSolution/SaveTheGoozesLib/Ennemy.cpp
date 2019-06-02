#include "pch.h"
#include "Ennemy.h"


Ennemy::Ennemy(int pv, float speed, b2World& world, std::string textureName, float positionX , float positionY) :
	Character(pv, speed, world,textureName,positionX,positionY)
{
}

