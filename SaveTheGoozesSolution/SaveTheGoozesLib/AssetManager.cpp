#include "pch.h"
#include "AssetManager.h"

#include<string>
#include <iostream>
#include <cassert>

std::unique_ptr<AssetManager> AssetManager::_instance;

void AssetManager::loadTexture(std::string const& textureName, std::string const& texturePath) {
	auto texture = std::make_unique<sf::Texture>();
	assert(texture->loadFromFile(texturePath) == true);
	_textures.insert({ textureName, std::move(texture) });
}


/* Pr� condition : la texture existe bien */
sf::Texture* AssetManager::getTexture(std::string const& textureName) {
	return _textures[textureName].get();
}