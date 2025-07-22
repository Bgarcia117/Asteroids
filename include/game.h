#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <vector>
#include <list>
#include <entity.h>

class Game {
public:
	static void init();
	static void begin();
	static void update(sf::RenderTarget& target, float deltaTime);

	static void gameOver();

	static std::vector<Entity*> entities;
	static std::list<std::vector<Entity*>::const_iterator> toRemoveList;
	static std::list<Entity*> toAddList;

	static size_t score;

	static sf::SoundBuffer shootSoundBuffer;
	static std::optional<sf::Sound> shootSound;

private:
	static float asteroidSpawnTime;
	static size_t highScore;
	static sf::Font font;

	static std::optional<sf::Text> scoreText;

	static std::optional<sf::Text> titleText;
	static std::optional<sf::Text> playText;

	static std::optional<sf::Text> highScoreText;
	static std::optional<sf::Text> gameOverText;
	static std::optional<sf::Text> continueText;
	static std::optional<sf::Text> menuText;


	static enum GameState { MENU, PLAYING, GAME_OVER } state;
};