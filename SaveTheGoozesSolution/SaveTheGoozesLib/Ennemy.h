#pragma once
#include "Character.h"
class Ennemy : public Character
{
public:
	Ennemy(int pv, float speed, b2World& world, std::string textureName);

};

