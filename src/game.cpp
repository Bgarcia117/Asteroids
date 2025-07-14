#include "game.h"
#include "asteroid.h"
#include "player.h"

std::vector<Entity*> Game::entities{};
std::list<std::vector<Entity*>::const_iterator> Game::toRemoveList{};
std::list<Entity*> Game::toAddList{};
float Game::asteroidSpawnTime{};

void Game::begin() {
	entities.push_back(new Player());
	asteroidSpawnTime = ASTEROID_SPAWN_TIME;
}

void Game::update(sf::RenderTarget& target, float deltaTime) {
	toAddList.clear();
	toRemoveList.clear();
	target.clear();

	for (size_t i = 0; i < entities.size(); i++) {
		entities[i]->update(deltaTime);
		entities[i]->render(target);
	}

	for (const auto& it : toRemoveList) {
		delete* it;
		entities.erase(it);
	}

	for (auto& ptr : toAddList) {
		entities.push_back(ptr);
	}

	asteroidSpawnTime -= deltaTime;
	if (asteroidSpawnTime <= 0) {
		entities.push_back(new Asteroid());
		asteroidSpawnTime = ASTEROID_SPAWN_TIME;
	}
}