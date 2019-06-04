#include "pch.h"
#include "WorldContactListener.h"
#include <iostream>
#include "Player.h"
#include "Ennemy.h"


WorldContactListener::WorldContactListener(b2World& world) : world(world) {}

void WorldContactListener::BeginContact(b2Contact* contact) {
	auto bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	auto bodyuserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	auto isSensor = (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor());

	if (static_cast<Player*>(bodyUserDataA)) {
		auto player = static_cast<Player*>(bodyUserDataA);
		if (static_cast<Ennemy*>(bodyuserDataB)) {
			auto enemy = static_cast<Ennemy*>(bodyuserDataB);
			if (!isSensor)
				player->takeDamage(enemy->getDamage());
			else
				std::cout << "Je pourrais attaquer le Renard" << std::endl;
			/*std::cout << "Je pourrais attaquer le Renard" << std::endl;
			if (player->isAttacking) {
				enemy->takeDamage(player->getDamage());
			}*/
		}
	}
}

void WorldContactListener::EndContact(b2Contact* contact) {
}