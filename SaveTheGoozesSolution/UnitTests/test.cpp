#include "pch.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>

#include "../SaveTheGoozesLib/SFMLOrthogonalLayer.hpp"
#include <tmxlite/detail/Log.hpp>
#include "../SaveTheGoozesLib/AssetManager.h"
#include "../SaveTheGoozesLib/Player.h"
#include "../SaveTheGoozesLib/Level.h"


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);



}






TEST(TestLevel, TestConstructeur) {
	sf::RenderWindow window(sf::VideoMode(1200, 1200), "SFML works!");
	auto assetManager = AssetManager::getInstance();
	assetManager->loadTexture("Alfonso", "../Game/Assets/Sprites/Alfonso.png");
	assetManager->loadTexture("Alfonso_hit", "../Game/Assets/Sprites/Alfonso_hit.png");
	assetManager->loadTexture("Bertrand", "../Game/Assets/Sprites/Bertrand.png");
	assetManager->loadTexture("Bertrand_hit", "../Game/Assets/Sprites/Bertrand_hit.png");
	assetManager->loadTexture("Coeur", "../Game/Assets/UI/coeur.png");
	assetManager->loadTexture("Gooze", "../Game/Assets/Sprites/Gooze.png");
	assetManager->loadTexture("Gooze_hit", "../Game/Assets/Sprites/Gooze_hit.png");
	Level levelTest("test","../Game/Assets/Tiled_Map/map_test01.tmx","../Game/ennemies_level01.json",window);
	EXPECT_TRUE(levelTest.invariant());
	//EXPECT_TRUE(true);
}

TEST(TestUI, TestinitChoix) {
	sf::RenderWindow window(sf::VideoMode(1200, 1200), "SFML works!");
	UserInterface gui(window);
	auto assetManager = AssetManager::getInstance();
	assetManager->loadTexture("Coeur", "../Game/Assets/UI/coeur.png");
	gui.initChoix();

	EXPECT_TRUE(gui.invariant());
}

TEST(TestUI, Testinit) {
	sf::RenderWindow window(sf::VideoMode(1200, 1200), "SFML works!");
	UserInterface gui(window);
	auto assetManager = AssetManager::getInstance();
	assetManager->loadTexture("Alfonso", "../Game/Assets/Sprites/Alfonso.png");
	assetManager->loadTexture("Coeur", "../Game/Assets/UI/coeur.png");
	b2World world(b2Vec2{ 0, 0 });
	auto playerPtr = std::make_unique<Player>(40.0f, 3, 1, world, 134, 97, 32, "Alfonso", 512, 512);

	gui.init(playerPtr.get());

	EXPECT_TRUE(gui.invariant());
}

TEST(TestUI, TestPerdUnCoeur) {
	sf::RenderWindow window(sf::VideoMode(1200, 1200), "SFML works!");
	UserInterface gui(window);
	auto assetManager = AssetManager::getInstance();
	assetManager->loadTexture("Alfonso", "../Game/Assets/Sprites/Alfonso.png");
	assetManager->loadTexture("Coeur", "../Game/Assets/UI/coeur.png");
	b2World world(b2Vec2{ 0, 0 });
	auto playerPtr = std::make_unique<Player>(40.0f, 3, 1, world, 134, 97, 32, "Alfonso", 512, 512);

	gui.init(playerPtr.get());
	gui.initChoix();
	gui.onNotify(Events::PlayerTakeDamage);

	EXPECT_TRUE(gui.invariant());
}


TEST(TestUI, TestPerd3Coeur) {
	sf::RenderWindow window(sf::VideoMode(1200, 1200), "SFML works!");
	UserInterface gui(window);
	auto assetManager = AssetManager::getInstance();
	assetManager->loadTexture("Alfonso", "../Game/Assets/Sprites/Alfonso.png");
	assetManager->loadTexture("Coeur", "../Game/Assets/UI/coeur.png");
	b2World world(b2Vec2{ 0, 0 });
	auto playerPtr = std::make_unique<Player>(40.0f, 3, 1, world, 134, 97, 32, "Alfonso", 512, 512);

	gui.init(playerPtr.get());
	gui.initChoix();
	gui.onNotify(Events::PlayerTakeDamage);
	gui.onNotify(Events::PlayerTakeDamage);
	gui.onNotify(Events::PlayerTakeDamage);

	EXPECT_TRUE(gui.invariant());
}


TEST(TestUI, TestPlayerDied) {
	sf::RenderWindow window(sf::VideoMode(1200, 1200), "SFML works!");
	UserInterface gui(window);
	auto assetManager = AssetManager::getInstance();
	assetManager->loadTexture("Alfonso", "../Game/Assets/Sprites/Alfonso.png");
	assetManager->loadTexture("Coeur", "../Game/Assets/UI/coeur.png");
	b2World world(b2Vec2{ 0, 0 });
	auto playerPtr = std::make_unique<Player>(40.0f, 3, 1, world, 134, 97, 32, "Alfonso", 512, 512);

	gui.init(playerPtr.get());
	gui.initChoix();
	gui.onNotify(Events::PlayerDied);


	EXPECT_TRUE(gui.invariant());
}