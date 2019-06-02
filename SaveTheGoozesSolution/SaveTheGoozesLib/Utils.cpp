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

b2Vec2 Utils::normalize(b2Vec2& vect) {
	float magnitude = sqrt(vect.x * vect.x + vect.y * vect.y);
	if (magnitude != 0.0) {
		vect.x /= magnitude;
		vect.y /= magnitude;
		return vect;
	}
	else {
		return vect;
	}

}