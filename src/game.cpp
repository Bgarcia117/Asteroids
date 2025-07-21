#include <iostream>
#include "game.h"
#include "asteroid.h"
#include "player.h"

std::vector<Entity*> Game::entities{};
std::list<std::vector<Entity*>::const_iterator> Game::toRemoveList{};
std::list<Entity*> Game::toAddList{};

size_t Game::score{};
float Game::asteroidSpawnTime{};

sf::Font Game::font{};
std::optional<sf::Text> Game::scoreText{};

sf::SoundBuffer Game::shootSoundBuffer{};
std::optional<sf::Sound> Game::shootSound{};

void Game::begin() {

	if (!font.openFromFile("assets/fonts/font.ttf")) {
		std::cerr << "ERROR::GAME::Failed to load font!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	scoreText = sf::Text(font);
	scoreText->setPosition(sf::Vector2f(40, 20));
	scoreText->setCharacterSize(48); // Set to 30 by default

	if (!shootSoundBuffer.loadFromFile("assets/sounds/shoot.wav")) {
		std::cerr << "Failed to load shoot.wav" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	shootSound = sf::Sound(shootSoundBuffer);

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

	scoreText->setString(std::to_string(score));
	target.draw(*scoreText);
}