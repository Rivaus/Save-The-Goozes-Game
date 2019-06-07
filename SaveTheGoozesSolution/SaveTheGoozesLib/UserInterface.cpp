#include "pch.h"
#include "UserInterface.h"


UserInterface::UserInterface(sf::RenderWindow& window):
	_gui(window)
{
}

void UserInterface::initChoix() {
	auto choix = tgui::Button::create();
	choix->setText("Slide on your life like a master");
	choix->setPosition(100, 100);
	choix->setSize(100, 100);
	choix->connect("pressed", [=]() { _gui.remove(choix); std::cout << "Music is my medecine" << std::endl; });
	_gui.add(choix);


	auto choix2 = tgui::Button::create();
	choix2->setText("Hit your head with your strength");
	choix2->setPosition(300, 100);
	choix2->setSize(100, 100);
	choix2->connect("pressed", [=]() { _gui.remove(choix2); std::cout << "I pledge my allegiance, to rythm and sound" << std::endl; });
	_gui.add(choix2);
}

void UserInterface::perdUneVie() {
	for (int i = nbViesPerdues; i >= 0;i--) {	
		_gui.remove(_viesJoueur[2-i]);
	}
	nbViesPerdues++;
}

void UserInterface::ressucite(){
	nbViesPerdues = 0;
	for (auto coeur : _viesJoueur) {
			_gui.add(coeur);
	}
}


void UserInterface::draw() {
	_gui.draw();
}

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

void UserInterface::handleEvents(sf::Event event) {
	bool retBool = _gui.handleEvent(event);
	if (retBool&&event.type==9) {
		std::cout << "l'event MousePressed a ete consomme : x = "<< event.mouseButton.x <<", y = "<< event.mouseButton.y <<std::endl;
		if (event.mouseButton.x > 100 && event.mouseButton.x < 200 && event.mouseButton.y>100 && event.mouseButton.y < 200) {
			std::cout << "le choix 1 est cliquey" << std::endl;
		}else if (event.mouseButton.x > 300 && event.mouseButton.x < 400 && event.mouseButton.y>100 && event.mouseButton.y < 200) {
			std::cout << "le choix 2 est cliquey" << std::endl;
		}
	}
}

void UserInterface::init() {
	float tailleX = 100.0f;
	float tailleY = 100.0f;
	for (int i = 0; i < 3; i++) {
		auto picture = createVie(tailleX, tailleY, 10 + tailleX * i, 10);
		_gui.add(picture,"coeur"+i);
		_viesJoueur.push_back(picture);
	}


	auto objectifLabel = tgui::Label::create();
	objectifLabel->setText("Objectif : Catch the goose !  or as they say in france 'chope l'oie' !");
	objectifLabel->setPosition(400, 10);
	objectifLabel->setTextSize(20);
	_gui.add(objectifLabel);

}

//fonction utilis� dans l'initialisation uniquement
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

void UserInterface::update() {
	_gui.draw();
}