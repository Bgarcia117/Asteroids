#pragma once
#include <numbers>
#include <random>

#include "global.h"
#include "entity.h"

const float ASTEROID_WIDTH = 80.f;
const float ASTEROID_HEIGHT = 80.f;
const float ASTEROID_SPIN = 20.f;
const float ASTEROID_SPEED = 180.f;
const float ASTEROID_SPAWN_TIME = 3.f;

class Asteroid : public Entity {
public:
	Asteroid(sf::Vector2f position = getRandomPosition(),
		     sf::Vector2f direction = Asteroid::getRandomDirection());


	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;

	static sf::Vector2f getRandomDirection();
	static sf::Vector2f getRandomPosition();

private:
	sf::Vector2f direction;
	sf::VertexArray shape;
};