#pragma once
#include <SFML\Audio.hpp>
#include "entity.h"

class Player : public Entity {
public:
	Player();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;

private:
	std::optional<sf::Sound> shootSound;  // Uses sounds
	sf::VertexArray shape;
	
	float shootTimer;
};

