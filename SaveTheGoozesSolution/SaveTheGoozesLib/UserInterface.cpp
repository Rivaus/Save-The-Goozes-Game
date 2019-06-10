#include "pch.h"
#include "UserInterface.h"
#include "Player.h"

//constructeur de Userinterface
UserInterface::UserInterface(sf::RenderWindow& window):
	_gui(window)
{
}

//initialisation des choix
void UserInterface::initChoix() {
	int tailleX = 600;
	int tailleY = 600;
	int positionX = 30;
	int positionY = 50;
	int offsetX = 20;
	int textSize = 35;


	//creation du premier bouton
	auto choix = tgui::Button::create();
	choix->setText("J'ai envie de patiner aujourdhui \n et rien ne m'en empeche \n car je suis libre de faire  \n  ce qu'il me plait");
	choix->setPosition(positionX, positionY);
	choix->setSize(tailleX, tailleY);
	choix->setTextSize(textSize);
	
	
	//pour la creation du deuxieme bouton on se decale sur l'axe X
	positionX += tailleX + offsetX;

	//creation du deuxieme bouton, on aurais aussi pu copier le premier et changer son texte et sa position
	auto choix2 = tgui::Button::create();
	choix2->setText("Je vais tester ma force \n en me frappant la tete");
	choix2->setPosition(positionX, positionY);
	choix2->setSize(tailleX, tailleY);
	choix2->setTextSize(textSize);

	//On associe l'action de presser l'un des deux boutons au choix dans le jeu, et on fait disparaitre les 2 boutons
	choix->connect("pressed", [=]() { _gui.remove(choix); _gui.remove(choix2); std::cout << "Music is my medecine" << std::endl;
	_player->setChoix(Choix::Slide); });
	choix2->connect("pressed", [=]() {_gui.remove(choix); _gui.remove(choix2); std::cout << "I pledge my allegiance, to rythm and sound" << std::endl;
	_player->setChoix(Choix::Confus); });

	//on ajoute les deux boutons a l'UI
	_gui.add(choix);
	_gui.add(choix2);
}

//fonction privée associée a l'evenement "le joueur perd une vie"
//on fait disparaitre le coeur le plus a droite et on increment le compteur de vie perdu
void UserInterface::perdUneVie() {
	for (int i = nbViesPerdues; i >= 0;i--) {	
		_gui.remove(_viesJoueur[2-i]);
	}
	nbViesPerdues++;
}

//fonction privée associée a l'évenement "le joueur meurt et ressucite"
//on fait réapparaitre tout ses coeurs et on ré-initilise le compteur de vie perdues
void UserInterface::ressucite(){
	nbViesPerdues = 0;
	for (auto coeur : _viesJoueur) {
			_gui.add(coeur);
	}
}

//focntion pour affcher l'ui
void UserInterface::draw() {
	_gui.draw();
}

//n'est pas utiliser car nous utilisons pas les evenements SFML
//permet de gerer les evenements 
void UserInterface::onNotify(sf::Event event) {
	switch (event.type)
	{
	case 0:
	{
		perdUneVie();
	}
	break;
	}
}

//permet de gerer les events "perd une vie" et "meurt et ressucite"
void UserInterface::onNotify(Events event) {
	switch (event)
	{
	case Events::PlayerTakeDamage:
		perdUneVie();
		break;
	case Events::PlayerDied:
		ressucite();
		break;
	}
	_gui.draw();
}

//permet de gerer les evenements sfml comme "on clique avec la souris sur un bouton"
//transmet l'evenement aux boutons de l'UI
void UserInterface::handleEvents(sf::Event event) {
	bool retBool = _gui.handleEvent(event);
	/*if (retBool&&event.type==9) {
		std::cout << "l'event MousePressed a ete consomme : x = "<< event.mouseButton.x <<", y = "<< event.mouseButton.y <<std::endl;
		if (event.mouseButton.x > 100 && event.mouseButton.x < 200 && event.mouseButton.y>100 && event.mouseButton.y < 200) {
			std::cout << "le choix 1 est cliquey" << std::endl;
		}else if (event.mouseButton.x > 300 && event.mouseButton.x < 400 && event.mouseButton.y>100 && event.mouseButton.y < 200) {
			std::cout << "le choix 2 est cliquey" << std::endl;
		}
	}*/
}

//fonction pour initiliser l'UI en jeu faisant apparaitre la vie du joueurs et un texte precisant son objectif
void UserInterface::init(Player *player) {
	float tailleX = 100.0f;
	float tailleY = 100.0f;
	for (int i = 0; i < 3; i++) {
		auto picture = createVie(tailleX, tailleY, 10 + tailleX * i, 10);
		_gui.add(picture,"coeur"+i);
		_viesJoueur.push_back(picture);
	}
	_player = player;

	auto objectifLabel = tgui::Label::create();
	objectifLabel->setText("Objectif : Catch the goose !  or as they say in france 'chope l'oie' !");
	objectifLabel->setPosition(400, 10);
	objectifLabel->setTextSize(20);
	_gui.add(objectifLabel);

}

//fonction utilisé dans l'initialisation uniquement
//creer les coeurs de la vie du joueur
tgui::Picture::Ptr UserInterface::createVie(float tailleX, float tailleY, float positionX, float positionY) {
	sf::Texture texture = *AssetManager::getInstance()->getTexture("Coeur");
	sf::Sprite  sprite;
	sprite.setTexture(texture);
	sprite.setScale(tailleY / texture.getSize().x, tailleX / texture.getSize().y);

	/*sf::Text text{ "Vie restante", *_gui.getFont(), 24 };
	text.setPosition(25, 100);
	text.setFillColor({ 200, 200, 200 });*/

	auto picture = tgui::Picture::create(texture,true); //le true est pour la transparence
	//picture->setInheritedOpacity(0.5f);

	picture->setPosition(positionX, positionY);
	//picture->draw(text);

	return picture;
}

//n'est pas utilisé car ca se met a jour tout seul avec les events
void UserInterface::update() {
	_gui.draw();
}