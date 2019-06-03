#pragma once

#include <Box2D/Box2D.h>

class WorldContactListener : public b2ContactListener
{
public:
	WorldContactListener(b2World& world);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

private :
	b2World& world;
};

