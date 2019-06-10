#include "pch.h"
#include "RaycastCallback.h"


RaycastCallback::RaycastCallback(Player* player) : player(player) {}

/*
Callback appel� � chaque fois qu'un raycast envoy� par le joueur (avec la touche d'action d'attaque) touche
un autre body. Declenche uen action si ce dernier appartient � un ennemi.
*/

float32 RaycastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
	float32 res = -1.f;

	auto ennemy = fixture->GetBody()->GetUserData();
	if (static_cast<Ennemy*>(ennemy)) {
		auto fox = static_cast<Ennemy*>(ennemy);
		fox->takeDamage(player->getDamage());
		res = 1.f;
	}

	return res;
}