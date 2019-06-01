#include "pch.h"
#include "Level.h"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <array>
#include <tmxlite/Map.hpp>

#include "InputManager.h"
#include "Utils.h"

Level::Level(std::string const name, std::string const mapPath, sf::RenderWindow& window) :
	_name(name), _world(b2Vec2{ 0, 0 }),
	_window(window), _clock(),
	_view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window.getSize().x, window.getSize().y))
{

	// On charge la TiledMap
	tmx::Map map;
	if (!map.load(mapPath)) {
		std::cout << "Unfortunately, the tiled map was not successfully loaded.";
	}
	_layers[0] = std::make_unique<MapLayer>(map, 0);
}

void Level::plays() {

	while (_window.isOpen())
	{
		sf::Event ev;

		while (_window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				_window.close();
		}



		sf::Time duration = _clock.getElapsedTime();
		float deltaTime = duration.asSeconds();

		_layers[0]->update(duration);
		update(deltaTime);


		_window.clear();
		_window.draw(*_layers[0]);
		_window.display();
	}
}

void Level::update(float deltaTime) {
	InputManager* inputMng = InputManager::getInstance();
	sf::Vector2f direction(inputMng->getAxis("Horizontal"), inputMng->getAxis("Vertical"));

	direction = Utils::normalize(direction) * deltaTime * 1.0f;
	std::cout << "Axis : " << direction.x << "; " << direction.y << std::endl;

	_view.move(direction);
	_window.setView(_view);
}