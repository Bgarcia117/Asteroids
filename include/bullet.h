#pragma once
#include "entity.h"

constexpr float SHOOT_DELAY = 0.2f;
constexpr float	BULLET_SPEED = 400.f;
constexpr float BULLET_LIFE = 3.f;

class Bullet : public Entity {
public:
	Bullet(sf::Vector2f position, sf::Vector2f direction);

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;

private:
	sf::CircleShape shape;
	sf::Vector2f direction;
	float lifetime;
};