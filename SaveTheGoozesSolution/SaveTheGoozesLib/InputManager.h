#pragma once
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

// Classe qui g�re toutes les entr�es du clavier et des Joystick;

class InputManager
{
private:
	static std::unique_ptr<InputManager> _instance;

public:
	static InputManager* getInstance();

	float getAxis(std::string axis);
};

