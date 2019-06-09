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

TEST(TestPlayer, Test1) {
	b2World world(b2Vec2{ 0, 0 });
	//Player player(5.0f,3,10,world,2,2,2);
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);



}



//ca compile pas et je sais pas pourquoi wouhou

TEST(TestConstructeurLevel, Test1) {
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
