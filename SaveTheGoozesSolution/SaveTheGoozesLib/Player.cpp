#include "pch.h"
#include "Player.h"



Player::Player(float speed,int pv,  b2World& world, std::string textureName, float positionX , float positionY ):
	Character(speed, pv,  world, textureName, positionX, positionY)
{
}



