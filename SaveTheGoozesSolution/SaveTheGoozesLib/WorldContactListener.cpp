#include "pch.h"
#include "WorldContactListener.h"
#include <iostream>


void WorldContactListener::BeginContact(b2Contact* contact) {
	std::cout << "On se rentre dedans !" << std::endl;
}

void WorldContactListener::EndContact(b2Contact* contact) {
	std::cout << "On se dit au revoir !" << std::endl;
}