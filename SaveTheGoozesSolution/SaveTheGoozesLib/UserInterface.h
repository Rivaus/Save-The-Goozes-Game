#pragma once
#include <TGUI/TGUI.hpp>
#include "AssetManager.h"
#include "Character.h"

enum class Events {
	PlayerTakeDamage,
	PlayerDied
};


class UserInterface
{
public:
	UserInterface(sf::RenderWindow& window);

	void draw();

	void handleEvent(sf::Event event);
	void onNotify(sf::Event event);
	void onNotify(Events event);
	void init();

	tgui::Picture::Ptr createVie(float tailleX, float tailleY, float positionX, float positionY);
	
	void update(int pvJoueur);

private:
	void perdUneVie();
	void ressucite();

private:
	tgui::Gui _gui;
	std::vector<tgui::Picture::Ptr> _viesJoueur;
};

