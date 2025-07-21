#pragma once
#include <SFML\Audio.hpp>
#include "entity.h"

class Player : public Entity {
public:
	Player();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;

private:
	sf::VertexArray shape;
	
	float shootTimer;
};

