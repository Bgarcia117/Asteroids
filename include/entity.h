#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
	Entity(sf::Vector2f position, float angle)
		: position(position), angle(angle) {

	}

	// Setting them to zero turns them into pure virtual functions
	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

	sf::Vector2f position;
	float angle;
};