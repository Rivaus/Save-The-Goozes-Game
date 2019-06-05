#pragma once
#include <TGUI/TGUI.hpp>
#include "AssetManager.h"

class UserInterface
{
public:
	UserInterface(sf::RenderWindow& window);

	void draw();

	void handleEvent(sf::Event event);

	void init();

	tgui::Picture::Ptr createVie(float tailleX, float tailleY, float positionX, float positionY);
	
	void update(int pvJoueur);
private:
	tgui::Gui _gui;
	std::vector<tgui::Picture::Ptr> _viesJoueur;
};

