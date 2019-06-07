#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

// Classe qui gère toutes les entrées du clavier et des Joystick;

class AssetManager
{
private:
	static std::unique_ptr<AssetManager> _instance;
	std::unordered_map <std::string, std::unique_ptr<sf::Texture>> _textures;

public:
	static AssetManager* getInstance() {
		static auto _instance = std::make_unique<AssetManager>();
		return _instance.get();
	}

	sf::Texture* getTexture(std::string const& textureName);

	void loadTexture(std::string const& textureName, std::string const& texturePath);
};

