#include "pch.h"
#include "WorldContactListener.h"
#include <iostream>
#include "Player.h"
#include "Ennemy.h"

void WorldContactListener::BeginContact(b2Contact* contact) {
	std::cout << "On se rentre dedans !" << std::endl;
	auto bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	auto bodyuserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (static_cast<Player*>(bodyUserDataA)) {
		auto player = static_cast<Player*>(bodyUserDataA);
		if (static_cast<Ennemy*>(bodyuserDataB)) {
			auto enemy = static_cast<Ennemy*>(bodyuserDataB);
			std::cout << "Le jour carresse un renard" << std::endl;
		}
	}
}

void WorldContactListener::EndContact(b2Contact* contact) {
	std::cout << "On se dit au revoir !" << std::endl;
}