#include "pch.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>

#include "../SaveTheGoozesLib/SFMLOrthogonalLayer.hpp"
#include <tmxlite/detail/Log.hpp>

#include "../SaveTheGoozesLib/Player.h"
#include "../SaveTheGoozesLib/Level.h"

int monMainQuentin()
{
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	window.setFramerateLimit(60);

	Level level1("Niveau test", "Assets/Tiled_Map/map_test01.tmx", "ennemies_level01.json", window);

	level1.plays();

	return 0;

}
