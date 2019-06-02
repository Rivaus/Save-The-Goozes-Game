#include "pch.h"
#include "Level.h"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <array>
#include <tmxlite/Map.hpp>
#include <vector>
#include <jsoncons/json.hpp>
#include <fstream>  

using namespace jsoncons;

#include "InputManager.h"
#include "Utils.h"

Level::Level(std::string const& name, std::string const& mapPath, std::string const& enemiesFilePath, sf::RenderWindow& window) :
	_name(name), _world(b2Vec2{ 0, 0 }),
	_window(window), _clock(),
	_view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window.getSize().x, window.getSize().y)),
	player(400.0f, 10, _world, 134, 97, 32, "Alfonso"),
	_enemies()
{
	//std::cout << "vitesse = " << player.speed << std::endl;
	// On charge la TiledMap
	tmx::Map map;
	if (!map.load(mapPath)) {
		std::cout << "Unfortunately, the tiled map was not successfully loaded.";
	}
	_layers[0] = std::make_unique<MapLayer>(map, 0);

	initPhysics(map);

	//On initialise les ennemis
	initEnemies(enemiesFilePath);
}


void Level::initPhysics(tmx::Map const& map) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody; //Elements qui ne bouge pas
	b2FixtureDef fixDef;
	b2PolygonShape shape;


	for (auto const& layer : map.getLayers()) {
		if (layer->getType() == tmx::Layer::Type::Object) {
			const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
			const auto& objects = objectLayer.getObjects();
			for (const auto& obj : objects)
			{
				bodyDef.position.Set(obj.getPosition().x + obj.getAABB().width /2 , obj.getPosition().y + obj.getAABB().height / 2);
				auto body = _world.CreateBody(&bodyDef);
				shape.SetAsBox(obj.getAABB().width / 2, obj.getAABB().height / 2);
				fixDef.shape = &shape;
				fixDef.density = 1;
				body->CreateFixture(&fixDef);
				std::cout << "Je suis un mur" << std::endl;
			}
		}
	}
}


void Level::initEnemies(std::string const& enemiesFilePath) {
	std::ifstream file(enemiesFilePath);
	jsoncons::json levelInitializer = jsoncons::json::parse(file);

	for (const auto& enemy : levelInitializer.array_range())
	{
		std::string name = enemy["name"].as<std::string>();
		float speed = enemy["speed"].as<float>();
		int pv = enemy["pv"].as_int();
		sf::Vector2f startPosition{ enemy["start_position"]["x"].as<float>(), enemy["start_position"]["y"].as<float>() };
		std::cout << name << " de vitesse " << speed << " a " << pv << std::endl;

		Ennemy e(pv, speed, _world, 281, 230, 0, "Bertrand", startPosition.x, startPosition.y);

		for (const auto& waypoint : enemy["waypoints"].array_range()) {
			e.addWaypoint(sf::Vector2f{ waypoint["x"].as<float>(), waypoint["x"].as<float>() });
		}

		_enemies.push_back(e);
	}
	file.close();
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
		player.draw(_window);
		for (auto const& e : _enemies) {
			e.draw(_window);
		}
		_window.display();
	}
}

void Level::update(float deltaTime) {
	_world.Step(1 / 60.f, 6, 2);
	_view.setCenter(player.getPosition());
	_window.setView(_view);
	player.update(deltaTime);
	for (auto& e : _enemies) {
		e.update(deltaTime);
	}
}