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
	_view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window.getSize().x, window.getSize().y)),
	player(400.0f,10,_world,"Alfonso")
{
	//std::cout << "vitesse = " << player.speed << std::endl;
	// On charge la TiledMap
	tmx::Map map;
	if (!map.load(mapPath)) {
		std::cout << "Unfortunately, the tiled map was not successfully loaded.";
	}
	_layers[0] = std::make_unique<MapLayer>(map, 0);


	initPhysics(map);
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
		_window.display();
	}
}

void Level::update(float deltaTime) {
	_world.Step(1 / 60.f, 6, 2);
	/*InputManager* inputMng = InputManager::getInstance();
	sf::Vector2f direction(inputMng->getAxis("Horizontal"), inputMng->getAxis("Vertical"));

	direction = Utils::normalize(direction) * deltaTime * 1.0f;
	//std::cout << "Axis : " << direction.x << "; " << direction.y << std::endl;
	*/
	//_view.move(direction);
	_view.setCenter(player.getPosition());
	_window.setView(_view);
	player.update(deltaTime);
}