#include "pch.h"
#include "Character.h"



Character::Character(float speed, int pv,int damage, b2World& world, int boxWidth, int boxHeight, int boxOffset, 
		std::string textureName, float positionX , float positionY) :
	speed(speed), pv(pv), damage(damage), sprite(), boxOffset(boxOffset), textures()
{
	textures.push_back(AssetManager::getInstance()->getTexture(textureName));
	textures.push_back(AssetManager::getInstance()->getTexture(textureName + "_hit"));

	sprite.setTexture(*textures[0]);
	sprite.setPosition(positionX, positionY);
	sprite.setOrigin(textures[0]->getSize().x / 2, textures[0]->getSize().x / 2);


	//Initialisation de la physique du character
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(positionX, positionY);
	body = world.CreateBody(&bodyDef);
	b2FixtureDef fixDef;
	b2PolygonShape shape;
	shape.SetAsBox(boxWidth / 2, boxHeight / 2);
	fixDef.shape = &shape;
	fixDef.density = .000001;
	body->CreateFixture(&fixDef);
	body->SetUserData(this);
}

void Character::update(float deltaTime)
{
	auto directionX = body->GetLinearVelocity().x;
	if (directionX < 0 && !isFlipped) {
		sprite.setScale(sf::Vector2f{ -scale, scale });
		isFlipped = true;
	}
	else if (directionX > 0 && isFlipped) {
		sprite.setScale(sf::Vector2f{ scale, scale });
		isFlipped = false;
	}
	sprite.setPosition(sf::Vector2f(body->GetPosition().x, body->GetPosition().y - boxOffset)); //ici le sprite suit le body
}

void Character::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

sf::Vector2f Character::getPosition()
{
	return sprite.getPosition();
}

int Character::getDamage() {
	return damage;
}


/*
Le character reçoit des dégats d'une valeur @damage. Si le personnage est touchable (i.e. canBeHit = true)
renvoie true pour signifier qu'il faut mettre à jour l'UI.
*/
bool Character::takeDamage(int damage) {
	bool updateUI = false;
	if (canBeHit) {
		pv -= damage;
		canBeHit = false;
		updateUI = true;
		sprite.setTexture(*textures[1]);
		auto t = std::thread(Character::waitForBeingHit, this, 2);
		t.detach();
		std::cout << "Je suis touche, je n ai plus que " << pv << " pv." << std::endl;
		if (pv <= 0) {
			std::cout << "Je suis mort. RIP." << pv << " pv." << std::endl;
			isDead = true;
		}
	}
	return updateUI;
}

/*
Fonction statique qui crée un thread permettant d'attendre @waitingTime
avant de rendre le personnage à nouveau touchable et lui remettre sa texture "normale".
*/
void Character::waitForBeingHit(Character* player, int waitingTime) {
	std::this_thread::sleep_for(std::chrono::seconds(waitingTime));
	player->canBeHit = true;
	player->sprite.setTexture(*player->textures[0]);
	std::cout << "Je peux etre a nouveau touche." << std::endl;
}