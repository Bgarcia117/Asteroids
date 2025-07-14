#include "player.h"
#include "bullet.h"
#include "global.h"
#include "game.h"

constexpr float PLAYER_WIDTH = 40.f;
constexpr float PLAYER_HEIGHT = 50.f;
constexpr float PLAYER_SPEED = 200.f;
constexpr float TURN_SPEED = 200.0f;

Player::Player()
	: Entity({ 500.f, 500.f }, 0.f), shape(sf::PrimitiveType::LineStrip, 5), shootTimer() {

	shape[0].position = { 0.f, -30.f };  // Tip
	shape[1].position = { 20.f, 20.f };  // Bottom Left
	shape[2].position = { 0.f, 10.f };   // Inward Dip
	shape[3].position = { -20.f, 20.f }; // Bottom Right
	shape[4].position = { 0.f, -30.f };  // Closes Shape

	/*
		VertexArray No longer provides begin() and end() so this cannot be used
	for (auto& vertex : shape) {
		vertex.color = sf::Color::Green;
	}
	*/

	for (std::size_t i = 0; i < shape.getVertexCount(); ++i) {
		shape[i].color = sf::Color::White;
	}
}


void Player::update(float deltaTime) {
	shootTimer -= deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
		angle -= TURN_SPEED * deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
		angle += TURN_SPEED * deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
		// Degrees -> Radian Equation: degrees * (PI/180)
		float radians = (angle - 90.f) * (PI / 180.f);

		position.x += cos(radians) * PLAYER_SPEED * deltaTime;
		position.y += sin(radians) * PLAYER_SPEED * deltaTime;

		// Max ensures that the position is never less than half the player's width
		// Min ensures the position is never more than the screen width/height - half of the player's width/height
		// This works bc the center is what we are moving meaning half is ahead of it
		// Known as "Clamping" used to pull player back in if they go out of bounds
		position.x = std::min(std::max(position.x, PLAYER_WIDTH / 2.f), SCREEN_WIDTH - PLAYER_WIDTH / 2.f);
		position.y = std::min(std::max(position.y, PLAYER_HEIGHT / 2.f), SCREEN_HEIGHT - PLAYER_HEIGHT / 2.f);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) && shootTimer <= 0.0f) {
		shootTimer = SHOOT_DELAY;
		float radians = (angle - 90.f) * (PI / 180.f);

		Game::toAddList.push_back(new Bullet(position, sf::Vector2f(cos(radians), sin(radians))));
	}

}


/**
	* @brief Draws the player ship to the given target
	*
	* Applies a transformation to position and rotates without modifying the shape
	*
	* @param target The SFML render target to draw to
	*/
void Player::render(sf::RenderTarget& target) {
	// Holds translation and rotation to be applied to shape when drawn
	sf::Transform transform;

	// Chains the operations together
	// Order matters. Shape moves then rotates
	transform.translate(position);

	// rotates() rotates the shape around the origin of the shape (0,0)
	transform.rotate(sf::degrees(angle));

	// Bundles Transform and tells SFML how to use it when drawing
	// Can carry shaders, textures, and blends modes. 
	// The only way to pass a transform to the draw() function
	// It also keeps the vertex coordinates centered around the shapes (0,0) 
	// If it is not used, it would assume its using (0,0) for the screen (top left)
	sf::RenderStates states;  // Apply this when drawing

	// Assign the transformation to the render state
	// SFML usses this to knows to apply it when drawing the shape.
	states.transform = transform;

	// Draw the shape (VertexArray) to the render target
	// Applies transformation at draw time without changing their actual values
	target.draw(shape, states);
}