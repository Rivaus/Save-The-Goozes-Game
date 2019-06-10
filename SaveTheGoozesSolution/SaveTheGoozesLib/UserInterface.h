#pragma once
#ifndef UI_DEF
#define UI_DEF


#include <TGUI/TGUI.hpp>
#include "AssetManager.h"

class Player;


enum class Events{
	PlayerTakeDamage,
	PlayerDied
};

enum class Choix {
	Slide,
	Confus
};


class UserInterface
{
public:
	UserInterface(sf::RenderWindow& window);

	void draw();

	void handleEvents(sf::Event event);
	void onNotify(Events event);
	void init(Player* player);
	void initChoix();
	bool invariant();
	tgui::Picture::Ptr createVie(float tailleX, float tailleY, float positionX, float positionY);


private:
	void perdUneVie();
	void ressucite();

private:
	tgui::Gui _gui;
	Player *_player;
	std::vector<tgui::Picture::Ptr> _viesJoueur;
	int nbViesPerdues = 0;
};

#endif // !UI_DEF