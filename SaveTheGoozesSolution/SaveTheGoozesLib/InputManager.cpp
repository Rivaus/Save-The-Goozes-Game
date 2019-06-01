#include "pch.h"
#include "InputManager.h"

#include<string>
#include <iostream>

std::unique_ptr<InputManager> InputManager::_instance;

InputManager* InputManager::getInstance() {
	if (!_instance) {
		_instance = std::make_unique <InputManager>();
	}
	return _instance.get();
}


// Renvoie 1 ou -1 si l'axe demandé est sollicité par le clavier ou le joystick
float InputManager::getAxis(std::string axis) {
	float direction = 0.0;

	if (axis.compare("Horizontal") == 0) {
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 10)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			direction = 1.0;
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < 10)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
			direction = -1.0;
	}
	else if (axis.compare("Vertical") == 0) {
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) < 10)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
			direction = -1.0;
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) > 10)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			direction = 1.0;
	}

	return direction;
}