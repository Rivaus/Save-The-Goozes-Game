#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Utils
{
public:
	static sf::Vector2f normalize(sf::Vector2f& vect);
	static b2Vec2 normalize(b2Vec2& vect);
};

