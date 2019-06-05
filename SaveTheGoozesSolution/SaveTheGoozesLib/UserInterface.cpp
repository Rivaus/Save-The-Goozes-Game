#include "pch.h"
#include "UserInterface.h"



UserInterface::UserInterface(sf::RenderWindow& window):
	_gui(window)
{
}

void UserInterface::draw() {
	_gui.draw();
}

void UserInterface::handleEvent(sf::Event event) {
	_gui.handleEvent(event);
}

void UserInterface::init() {
	float tailleX = 100.0f;
	float tailleY = 100.0f;
	for (int i = 0; i < 3; i++) {
		auto canvas = createVie(100.0f, 100.0f, 10 + tailleX * i, 10);
		canvas->display();
		_gui.add(canvas);
		_viesJoueur.push_back(canvas);
	}
}

//fonction utilisé dans l'initialisation uniquement
tgui::Canvas::Ptr UserInterface::createVie(float tailleX, float tailleY, float positionX, float positionY) {
	sf::Texture texture = *AssetManager::getInstance()->getTexture("Alfonso");
	sf::Sprite  sprite;
	sprite.setTexture(texture);
	sprite.setScale(tailleY / texture.getSize().x, tailleX / texture.getSize().y);

	/*sf::Text text{ "Vie restante", *_gui.getFont(), 24 };
	text.setPosition(25, 100);
	text.setFillColor({ 200, 200, 200 });*/

	auto canvas = tgui::Canvas::create({ tailleX, tailleY });
	canvas->setPosition(positionX, positionY);
	canvas->clear();
	canvas->draw(sprite);
	//canvas->draw(text);

	return canvas;
}

void UserInterface::update(int pvJoueur) {

}