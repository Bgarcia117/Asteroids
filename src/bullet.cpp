#include <algorithm> // For std::find
#include "bullet.h"
#include "game.h"
#include "asteroid.h"
#include "physics.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) :
	Entity(position, 0.f), shape(1.f), direction(direction), lifetime(BULLET_LIFE) {

}

void Bullet::update(float deltaTime) {
	lifetime -= deltaTime;
	position += direction * BULLET_SPEED * deltaTime;

	if (lifetime <= 0.f) {
		Game::toRemoveList.push_back(std::find(Game::entities.begin(),
			                                   Game::entities.end(), this));
	}

	// "Ray Casting Algorithm"
	// Loop through the entities in the game
	for (size_t i = 0; i < Game::entities.size(); i++) {

		// Check if the current entity is an asteroid
		if (typeid(*Game::entities[i]) == typeid(Asteroid)) {

			// If entity is an asteroid, dynamic cast to access members
			Asteroid* asteroid = dynamic_cast<Asteroid*>(Game::entities[i]);

			// Gets the shape of our asteroid
			const sf::VertexArray& polygon = asteroid->getVertexArray();

			// Checks where it is on screen using the position and angle
			// Applies position and angle to shape
			sf::Transform transform;
			transform.translate(asteroid->position);
			transform.rotate(sf::degrees(asteroid->angle));

			// Checks if the num  of intersections is even or odd
			// Imagine a line drawn over the shape, how many times does it overlap?
			if (physics::intersects(position,
				physics::getTransformed(asteroid->getVertexArray(), transform))) {

				lifetime = 0.f;

				Game::toRemoveList.push_back(std::find(Game::entities.begin(),
					                                   Game::entities.end(), asteroid));
				Game::score += 10;
			}
		}
	}
}

void Bullet::render(sf::RenderTarget& target) {
	target.draw(shape, sf::Transform().translate(position));

	// === Debug: Draw horizontal ray to the right ===
	/*
	sf::VertexArray ray(sf::PrimitiveType::LineStrip, 2);
	ray[0].position = position;
	ray[0].color = sf::Color::Cyan;
	ray[1].position = sf::Vector2f(1920.f, position.y); // or window.getSize().x
	ray[1].color = sf::Color::Cyan;

	target.draw(ray);
	*/
}

