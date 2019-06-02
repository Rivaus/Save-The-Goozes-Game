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

	//monMainLucas();
	monMainQuentin();
}
