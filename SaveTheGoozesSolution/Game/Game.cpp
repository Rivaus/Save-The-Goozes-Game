#include "pch.h"
#include <iostream>
#include "pch.h"
#include "testLucas.h"
#include "testQuentin.h"
#include "../SaveTheGoozesLib/AssetManager.h"

int main()
{

	auto assetManager = AssetManager::getInstance();
	assetManager->loadTexture("Alfonso", "Assets/Sprites/Alfonso.png");
	assetManager->loadTexture("Alfonso_hit", "Assets/Sprites/Alfonso_hit.png");
	assetManager->loadTexture("Bertrand", "Assets/Sprites/Bertrand.png");
	assetManager->loadTexture("Bertrand_hit", "Assets/Sprites/Bertrand_hit.png");
	assetManager->loadTexture("Coeur", "Assets/UI/coeur.png");
	assetManager->loadTexture("Gooze", "Assets/Sprites/Gooze.png");
	assetManager->loadTexture("Gooze_hit", "Assets/Sprites/Gooze_hit.png");

	//monMainLucas();
	monMainQuentin();
}
