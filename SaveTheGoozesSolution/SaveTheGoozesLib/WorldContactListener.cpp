#include "pch.h"
#include "WorldContactListener.h"
#include <iostream>
#include "Player.h"
#include "Ennemy.h"


WorldContactListener::WorldContactListener(b2World& world) : world(world) {}

void WorldContactListener::BeginContact(b2Contact* contact) {
	Character* bodyUserDataA = (Character*) contact->GetFixtureA()->GetBody()->GetUserData();
	Character* bodyuserDataB = (Character *) contact->GetFixtureB()->GetBody()->GetUserData();
	if (!bodyUserDataA || !bodyuserDataB) {
		return;
	}

	if (auto player = dynamic_cast<Player*>(bodyUserDataA)) {
		if (auto enemy = dynamic_cast<Ennemy*>(bodyuserDataB)) {
			player->takeDamage(enemy->getDamage());
		}
	}
}

void WorldContactListener::EndContact(b2Contact* contact) {
}