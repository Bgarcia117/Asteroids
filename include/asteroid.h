#pragma once

#include "entity.h"

constexpr float ASTEROID_WIDTH = 80.f;
constexpr float ASTEROID_HEIGHT = 80.f;
constexpr float ASTEROID_SPIN = 20.f;
constexpr float ASTEROID_SPEED = 180.f;
constexpr float ASTEROID_SPAWN_TIME = 3.f;

class Asteroid : public Entity {
public:
	Asteroid(sf::Vector2f position = getRandomPosition(),
		     sf::Vector2f direction = Asteroid::getRandomDirection());

	// override is only needed in .h b/c it is a compiler check
	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
	const sf::VertexArray& getVertexArray() const;

	static sf::Vector2f getRandomDirection();
	static sf::Vector2f getRandomPosition();

private:
	sf::Vector2f direction;
	sf::VertexArray shape;
};