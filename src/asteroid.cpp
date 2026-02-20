#include "asteroid.h"
#include "global.h"
#include <random>
#include <cmath>

Asteroid::Asteroid(sf::Vector2f position, sf::Vector2f direction)
	   : Entity(position, 0.f), direction(direction), shape(sf::PrimitiveType::LineStrip, 12), life(0.f) {

	shape[0].position = { -40.f, 40.f };
	shape[1].position = { -50.f, 10.f };
	shape[2].position = { -10.f, -20.f };
	shape[3].position = { -20.f, -40.f };
	shape[4].position = { 10.f, -40.f };
	shape[5].position = { 40.f, -20.f };
	shape[6].position = { 40.f, 10.f };
	shape[7].position = { 30.f, 0.f };
	shape[8].position = { 40.f, 20.f };
	shape[9].position = { 20.f, 40.f };
	shape[10].position = { 0.f, 30.f };
	shape[11].position = shape[0].position;

	for (std::size_t i = 0; i < shape.getVertexCount(); ++i) {
		shape[i].color = sf::Color::White;
	}
}

void Asteroid::update(float deltaTime) {
	life += deltaTime; // How long the asteroid has been alive

	position += ASTEROID_SPEED * direction * deltaTime;
	angle += ASTEROID_SPIN * deltaTime;

	// Absolute value prevents infinite loop if it goes out of bounds and keeps flipping
	if (position.x < ASTEROID_WIDTH / 2.f) {
		direction.x = std::abs(direction.x);
	}
	else if (position.x > SCREEN_WIDTH - ASTEROID_WIDTH / 2.f) {
		direction.x = -std::abs(direction.x);
	}

	if (position.y < ASTEROID_HEIGHT / 2.f) {
		direction.y = std::abs(direction.y);
	}
	else if (position.y > SCREEN_HEIGHT - ASTEROID_HEIGHT / 2.f) {
		direction.y = -std::abs(direction.y);
	}

}

void Asteroid::render(sf::RenderTarget& target) {
	// LineStrip shapes do not have an internal position or rotation
	// It is just a bunch of points, so we need to handle that with tranform
	// Handles movement, rotation, and scaling
	sf::Transform transform;
	transform.translate(position);
	transform.rotate(sf::degrees(angle));

	// Bundles together settings: transform, textures, shader, etc
	// To give draw()
	sf::RenderStates states;
	states.transform = transform;

	target.draw(shape, states);
}

const sf::VertexArray& Asteroid::getVertexArray() const {
	return shape;
}

// Static so it does not depend on an instance of the class
sf::Vector2f Asteroid::getRandomDirection() {
	std::random_device rd;  // Gets random seed from system

	std::mt19937 gen(rd()); // Seeded Generator

	// Dist obj generates floats uniformly
	// 2PI is a full circle in radians for bouncing around
	std::uniform_real_distribution<float> dist(0.f, 2.f * PI);

	// Calls the dist obj's operator to generate a number
	float angle = dist(gen);

	// Cosine gives an x and sine gives a y coordinate on a circle
	// Refer to the Unit Circle
	return sf::Vector2f(cos(angle), sin(angle));
}

sf::Vector2f Asteroid::getRandomPosition() {
	std::random_device rd;  // Gets random seed from system
	std::mt19937 gen(rd()); // Seeded Generator

	// Set distributions
	std::uniform_real_distribution<float> xAxis(ASTEROID_WIDTH / 2.f, SCREEN_WIDTH - ASTEROID_WIDTH / 2.f);
	std::uniform_real_distribution<float> yAxis(ASTEROID_HEIGHT / 2.f, SCREEN_HEIGHT - ASTEROID_HEIGHT / 2.f);

	return sf::Vector2f(xAxis(gen), yAxis(gen));
}