#pragma once

#include<SFML/Graphics.hpp>

class Character
{

public:
	Character(float speed, int pv) : speed(speed), pv(pv) {}

private:
	int pv;
	float speed;
	
};

