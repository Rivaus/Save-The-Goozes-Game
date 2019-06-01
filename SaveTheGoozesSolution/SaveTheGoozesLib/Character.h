#pragma once

#include<SFML/Graphics.hpp>

class Character
{

public:
	Character() : rect(sf::Vector2f(200, 200)) {
		rect.setFillColor(sf::Color::Red);
	}

	sf::RectangleShape& getRectangle() {
		return rect;
	}

private:
	sf::RectangleShape rect;
};

