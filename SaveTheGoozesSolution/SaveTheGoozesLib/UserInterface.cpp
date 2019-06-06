#include "pch.h"
#include "UserInterface.h"

/*Tu peux faire une sorte de mini pattern Observer. Dsns player,
tu rajoutes un pointeur/ou référence  vers ton uiInterface. 
Et dans Player, tu ovverides takeDamage (faut la passer en virtuel dsns Character du coup)
pour qu’elle appelle takeDamage de la mère + notifie ton UI*/

UserInterface::UserInterface(sf::RenderWindow& window):
	_gui(window)
{
}

void UserInterface::perdUneVie() {
	for (auto coeur : _viesJoueur) {
		if (coeur->isVisible()) {
			coeur->setVisible(false);
			_gui.draw();
			break;
		}
	}
}
void UserInterface::ressucite(){
	for (auto coeur : _viesJoueur) {
		if (!coeur->isVisible()) {
			coeur->setVisible(true);
		}
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
	std::cout << "Je suis notifier" << std::endl;
	switch (event)
	{
	case Events::PlayerTakeDamage:
	{
		perdUneVie();
	}
	case Events::PlayerDied:
	{
		ressucite();
	}
	break;
	}
	_gui.draw();
}

void UserInterface::handleEvent(sf::Event event) {
	_gui.handleEvent(event);
}

void UserInterface::init() {
	float tailleX = 100.0f;
	float tailleY = 100.0f;
	for (int i = 0; i < 3; i++) {
		auto picture = createVie(tailleX, tailleY, 10 + tailleX * i, 10);
		_gui.add(picture);
		_viesJoueur.push_back(picture);
	}


	auto objectifLabel = tgui::Label::create();
	objectifLabel->setText("Objectif : Catch the goose !  or as they say in france 'chope l'oie' !");
	objectifLabel->setPosition(400, 10);
	objectifLabel->setTextSize(20);
	_gui.add(objectifLabel);

}

//fonction utilisé dans l'initialisation uniquement
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

void UserInterface::update(int pvJoueur) {

}