#include "pch.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>

#include "../SaveTheGoozesLib/SFMLOrthogonalLayer.hpp"
#include <tmxlite/detail/Log.hpp>

#include "../SaveTheGoozesLib/Player.h"
#include "../SaveTheGoozesLib/Level.h"
#include "testLucas.h"

int monMainLucas()
{
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	window.setFramerateLimit(60);

	Player player(400.0f);

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
