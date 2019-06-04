#include "pch.h"
#include "WorldContactListener.h"
#include <iostream>
#include "Player.h"
#include "Ennemy.h"


WorldContactListener::WorldContactListener(b2World& world) : world(world) {}

void WorldContactListener::BeginContact(b2Contact* contact) {
	auto bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	auto bodyuserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	
	if (static_cast<Player*>(bodyUserDataA)) {
		auto player = static_cast<Player*>(bodyUserDataA);
		if (static_cast<Ennemy*>(bodyuserDataB)) {
			auto enemy = static_cast<Ennemy*>(bodyuserDataB);
			player->takeDamage(enemy->getDamage());
		}
	}
}

void WorldContactListener::EndContact(b2Contact* contact) {
}