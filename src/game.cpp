#include <iostream>
#include <fstream>
#include "game.h"
#include "asteroid.h"
#include "player.h"

std::vector<Entity*> Game::entities{};
std::list<std::vector<Entity*>::const_iterator> Game::toRemoveList{};
std::list<Entity*> Game::toAddList{};

size_t Game::score{};
size_t Game::highScore;
float Game::asteroidSpawnTime{};

Game::GameState Game::state{};

sf::Font Game::font{};
std::optional<sf::Text> Game::scoreText{};

std::optional<sf::Text> Game::titleText{};
std::optional<sf::Text> Game::playText{};

std::optional<sf::Text> Game::highScoreText{};
std::optional<sf::Text> Game::gameOverText{};
std::optional<sf::Text> Game::continueText{};
std::optional<sf::Text> Game::menuText{};

sf::SoundBuffer Game::shootSoundBuffer{};
std::optional<sf::Sound> Game::shootSound{};

void Game::init() {
	// Stores as binary instead of text
	std::ifstream file("score.dat", std::ios::binary | std::ios::in);

	if (file.is_open()) {
		// Casts to an int array of bytes
		file.read(reinterpret_cast<char*>(&highScore), sizeof(size_t));
		file.close();
	}

	if (!font.openFromFile("assets/fonts/font.ttf")) {
		std::cerr << "ERROR::GAME::Failed to load font!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	scoreText = sf::Text(font);
	scoreText->setPosition(sf::Vector2f(40, 20));
	scoreText->setCharacterSize(48); // Set to 30 by default

	// =====- Main Menu =======
	titleText = sf::Text(font);
	titleText->setPosition(sf::Vector2f(300, 300));
	titleText->setCharacterSize(128);
	titleText->setString("Asteroids");

	playText = sf::Text(font);
	playText->setPosition(sf::Vector2f(450, 500));
	playText->setCharacterSize(30);
	playText->setString("Press ENTER to play...");

	// ====== Game Over Screen ======
	gameOverText = sf::Text(font);
	gameOverText->setPosition(sf::Vector2f(250, 300));
	gameOverText->setCharacterSize(128);
	gameOverText->setString("Game Over!");

	continueText = sf::Text(font);
	continueText->setPosition(sf::Vector2f(400, 500));
	continueText->setCharacterSize(30);
	continueText->setString("Press ENTER to continue...");

	menuText = sf::Text(font);
	menuText->setPosition(sf::Vector2f(375, 550));
	menuText->setCharacterSize(30);
	menuText->setString("Press ESCAPE to exit to menu...");


	highScoreText = sf::Text(font);
	highScoreText->setPosition(sf::Vector2f(40, 20));
	highScoreText->setCharacterSize(48);
	highScoreText->setString("High Score: " + std::to_string(highScore));



	if (!shootSoundBuffer.loadFromFile("assets/sounds/shoot.wav")) {
		std::cerr << "Failed to load shoot.wav" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	shootSound = sf::Sound(shootSoundBuffer);

	state = MENU;
}

void Game::begin() {
	state = PLAYING;
	entities.push_back(new Player());
	asteroidSpawnTime = ASTEROID_SPAWN_TIME;
	score = 0;
}

void Game::update(sf::RenderTarget& target, float deltaTime) {

	if (state == MENU) {
		target.draw(*highScoreText);
		target.draw(*titleText);
		target.draw(*playText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter)) {
			begin();
		}

		return;
	}

	toAddList.clear();
	toRemoveList.clear();

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

	if (state == GAME_OVER) {
		entities.clear();
		target.draw(*gameOverText);
		target.draw(*continueText);
		target.draw(*menuText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter)) {
			begin();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) {
			state = MENU;
		}
	}
}

void Game::gameOver() {
	if (score > highScore) {
		highScore = score;
		std::ofstream file("score.dat", std::ios::binary | std::ios::out);

		if (file.is_open()) {
			file.write(reinterpret_cast<const char*>(&highScore), sizeof(size_t));
			file.close();
		}
		else {
			std::cerr << "Game::begin::Failed to write high score to file!" << std::endl;
		}

		highScoreText->setString("High Score: " + std::to_string(highScore));
	}

	state = GAME_OVER;
}