#include "pch.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>

#include "../SaveTheGoozesLib/SFMLOrthogonalLayer.hpp"
#include <tmxlite/detail/Log.hpp>

#include "../SaveTheGoozesLib/Player.h"
#include "../SaveTheGoozesLib/Level.h"
#include <Box2D/Box2D.h>
#include "testLucas.h"


int monMainLucas()
{
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	window.setFramerateLimit(60);
	//aled ca marche pas ici
	b2World world(b2Vec2{ 0, 0 });
	Player player(400.0f,5,world);

	sf::Clock globalClock;
	float deltaTime = 0.0f;
	while (window.isOpen())
	{
		sf::Event ev;

		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window.close();
		}
		deltaTime = globalClock.restart().asSeconds();

		window.clear();
		player.update(deltaTime);
		player.draw(window);
		window.display();
	}

	return 0;

}
