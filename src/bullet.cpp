#include <algorithm> // For std::find
#include "bullet.h"
#include "game.h"
#include "asteroid.h"

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

			
			size_t numOfVerticies = polygon.getVertexCount();
			size_t intersectionCount = 0;

			// Used for how long the ray starting at the bullet should be, wasn't used yet
			sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::max(), position.y);

			// Iterates over the vertex array
			for (size_t j = 0; j < numOfVerticies; j++) {
				// Treats the edge as a line
				// Turns the verticies into world coordinates
				sf::Vector2f p1 = transform.transformPoint(polygon[j].position);

				// %numOfVerticies accounts for the edge case of the last one polygon[11] and connects
				// it to the first vertex
				sf::Vector2f p2 = transform.transformPoint(polygon[(j + 1) % numOfVerticies].position);

				// Checks if the bullet would intersect if on the same level vertically
				if ((p1.y < position.y && p2.y >= position.y) ||
					(p2.y < position.y && p1.y >= position.y)) {

					// "Interpolation" used to check where bullet would hit along asteroid edge
					// Its a proportion, t=0 means its at p1, 1 = p2, and 0.5 is halfway
					float t = (position.y - p1.y) / (p2.y - p1.y);

					// Adds the t to find the edge x-axis would intersect with the bullet
					// p2.x - p1.x gives you the distance between them
					// Multiplying accounts for sloped edges
					float intersectX = p1.x + t * (p2.x - p1.x);

					// Checks if the asteroid intersects to the right and how many times
					if (intersectX < position.x) {
						intersectionCount++;
					}
				}
			}

			// Checks if the num  of intersections is even or odd
			// Imagine a line drawn over the shape, how many times does it overlap?
			if (intersectionCount % 2 == 1) {
				lifetime = 0.f;
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

