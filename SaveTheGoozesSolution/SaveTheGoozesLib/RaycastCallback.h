#pragma once
#include <Box2D/Box2D.h>
#include "Ennemy.h"
#include "Player.h"

class RaycastCallback : public b2RayCastCallback
{
public:
	RaycastCallback(Player* player);

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;

private:
	Player* player;
};

