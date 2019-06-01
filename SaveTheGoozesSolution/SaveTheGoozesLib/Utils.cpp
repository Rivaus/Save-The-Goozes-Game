#include "pch.h"
#include "Utils.h"


sf::Vector2f Utils::normalize(sf::Vector2f& vect) {
	float magnitude = sqrt(vect.x * vect.x + vect.y * vect.y);
	if (magnitude != 0.0) {
		return vect / magnitude;
	}
	else {
		return vect;
	}

}