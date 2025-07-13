#pragma once
#include "global.h"
#include "entity.h"

constexpr float PLAYER_WIDTH = 40.f;
constexpr float PLAYER_HEIGHT = 50.f;
constexpr float PLAYER_SPEED = 200.f;
constexpr float TURN_SPEED = 200.0f;

class Player : public Entity {
public:
	Player();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;

private:
	sf::VertexArray shape;
	float shootTimer;
};

