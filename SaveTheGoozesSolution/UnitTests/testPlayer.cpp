#include "pch.h"
#include "../SaveTheGoozesLib/Player.h"
#include "../SaveTheGoozesLib/AssetManager.h"
#include "../SaveTheGoozesLib/WorldContactListener.h"
#include <Box2D/Box2D.h>

TEST(TestPlayer, TestTakeDamage) {
	b2World world(b2Vec2_zero);

	auto assetManager = AssetManager::getInstance();
	assetManager->loadTexture("Alfonso", "../Game/Assets/Sprites/Alfonso.png");
	assetManager->loadTexture("Alfonso_hit", "../Game/Assets/Sprites/Alfonso_hit.png");

	sf::RenderWindow window(sf::VideoMode(10, 10), "SFML works!");

	UserInterface ui(window);
	Player player(100.0f, 3, 1, world, 200, 200, 0, "Alfonso");
	player.addUI(&ui);

	player.takeDamage(3.f);
	EXPECT_EQ(player.getPv(), 0);
	EXPECT_TRUE(player.dead());
}