#pragma once
#include <tmxlite/Map.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "SFMLOrthogonalLayer.hpp"

#include <array>
#include <string>


class Level
{
public:
	Level(std::string name, std::string mapPath, sf::RenderWindow& window);

	void plays();
	void update(float deltaTime);

private:
	std::array<std::unique_ptr<MapLayer>, 2> _layers;
	std::string _name;
	b2World _world;
	sf::RenderWindow& _window;
	sf::View _view;
	sf::Clock _clock;
	//std::vector<std::unique_ptr<GameObject>> gameobjects;
};

