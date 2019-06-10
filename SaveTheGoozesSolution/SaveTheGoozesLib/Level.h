#pragma once
#include <tmxlite/Map.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "SFMLOrthogonalLayer.hpp"

#include "Player.h"


#include "UserInterface.h"

#include "WorldContactListener.h"

#include <array>
#include <string>


class Level
{
public:
	Level(std::string const& name, std::string const& mapPath, std::string const& enemiesFilePath, sf::RenderWindow& window);

	void plays();
	void update(sf::Time duration);
	void draw();
	bool invariant();


private :
	void initPhysics(tmx::Map const& map);
	void initEnemies(std::string const& enemiesFilePath);
	void initGui(Player* player);

private:
	std::array<std::unique_ptr<MapLayer>, 2> _layers;
	std::string _name;
	b2World _world;
	sf::RenderWindow& _window;
	sf::View _view;
	sf::Clock _clock;
	Player* player;
	std::vector<std::unique_ptr<Character>> _characters;
	WorldContactListener _contactListener;
	UserInterface _gui;
};

