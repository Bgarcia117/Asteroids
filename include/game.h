#pragma once

#include <vector>
#include <list>
#include <entity.h>

class Game {
public:
	static void begin();
	static void update(sf::RenderTarget& target, float deltaTime);

	static std::vector<Entity*> entities;
	static std::list<std::vector<Entity*>::const_iterator> toRemoveList;
	static std::list<Entity*> toAddList;

private:
	float asteroidSpawnTime;
};