#include "pch.h"
#include "Level.h"
#include "Ennemy.h"
#include "Gooze.h"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <array>
#include <tmxlite/Map.hpp>
#include <vector>
#include <jsoncons/json.hpp>
#include <fstream>  
#include <algorithm>
#include <SFML/OpenGL.hpp>

using namespace jsoncons;

#include "Utils.h"

Level::Level(std::string const& name, std::string const& mapPath, std::string const& enemiesFilePath, sf::RenderWindow& window) :
	_name(name), _world(b2Vec2{ 0, 0 }),
	_window(window), _clock(),
	_view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window.getSize().x, window.getSize().y)),
	_characters(),
	_contactListener(),
	_gui(window)
{
	// On charge la TiledMap
	tmx::Map map;
	if (!map.load(mapPath)) {
		std::cout << "Unfortunately, the tiled map was not successfully loaded.";
	}
	_layers[0] = std::make_unique<MapLayer>(map, 0);
	_layers[1] = std::make_unique<MapLayer>(map, 1);

	initPhysics(map);

	//on crée le joueur
	auto playerPtr = std::make_unique<Player>(40.0f, 3, 1, _world, 134, 97, 32, "Alfonso");
	player = playerPtr.get();
	_characters.push_back(std::move(playerPtr));

	//On charge l'oie
	_characters.push_back(std::make_unique<Gooze>(0, 400, 1, _world, 206, 200, 0, "Gooze", GoozePower::Invincible, 600, 900));

	//On initialise les ennemis
	initEnemies(enemiesFilePath);

	//On initialise l'ui
	initGui(player);

	_view.zoom(4);
}


void Level::initPhysics(tmx::Map const& map) {
	// On initialise la gestion des collisions
	_world.SetContactListener(&_contactListener);

	// On ajoute des colliders à tous les "murs" de la map
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
			}
		}
	}
}


void Level::initEnemies(std::string const& enemiesFilePath) {
	std::ifstream file(enemiesFilePath);
	jsoncons::json levelInitializer = jsoncons::json::parse(file);

	for (const auto& enemy : levelInitializer.array_range())
	{
		auto name = enemy["name"].as<std::string>();
		auto speed = enemy["speed"].as<float>();
		auto pv = enemy["pv"].as_int();
		auto damage = enemy["damage"].as_int();
		auto textureName = enemy["texture"].as<std::string>();

		sf::Vector2f startPosition{ enemy["start_position"]["x"].as<float>(), enemy["start_position"]["y"].as<float>() };

		auto e  = std::make_unique<Ennemy>(speed,pv, damage, _world, 281, 180, 25, textureName, startPosition.x, startPosition.y);

		for (const auto& waypoint : enemy["waypoints"].array_range()) {
			e->addWaypoint(sf::Vector2f{ waypoint["x"].as<float>(), waypoint["y"].as<float>() });
		}
		
		_characters.push_back(std::move(e));
	}
	file.close();
}

void Level::initGui(Player* playerPtr) {
	_gui.init(playerPtr);
	_gui.initChoix();
	player->addUI(&_gui);
}

void Level::plays() {

	while (_window.isOpen())
	{
		sf::Event ev;

		while (_window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				_window.close();

			_gui.handleEvents(ev);//si il y a des events pour l'ui
		}

		sf::Time duration = _clock.getElapsedTime();
		float deltaTime = duration.asSeconds();
		_layers[0]->update(duration);
		_layers[1]->update(duration);
		update(deltaTime);

		_window.clear();
		_window.draw(*_layers[0]);
		_window.draw(*_layers[1]);

		/*std::sort(_characters.begin(), _characters.end(), [](auto& charA, auto& charB) {
			return charA->getPosition().y < charB->getPosition().y;
			});*/

		for (auto const& c : _characters) {
			c->draw(_window);
		}
		_gui.draw(); //draw l'ui
		_window.display();
	}
}

void Level::update(float deltaTime) {
	_world.Step(1 / 60.f, 6, 2);
	for (auto& c : _characters) {
		c->update(deltaTime);
	}
	_view.setCenter(player->getPosition());
	_window.setView(_view);
}

bool Level::invariant() {
	if (!player) {
		return false;
	}
	else if(!(_layers[0]&&_layers[1])){
		return false;
	}

	return true;
}