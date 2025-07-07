#include <iostream>
#include <numbers>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

constexpr float PI = 3.14159265f;
constexpr float TURN_SPEED = 200.0f;
constexpr float PLAYER_SPEED = 200.f;

class Player {
public: 
	Player()
		: shape(sf::PrimitiveType::LineStrip, 5), position(500.f, 500.f), angle(0.f) {
		shape[0].position = { 0.f, -30.f };  // Tip
		shape[1].position = { 20.f, 20.f };  // Bottom right
		shape[2].position = { 0.f, 10.f };   // Inward dip
		shape[3].position = { -20.f, 20.f }; // Bottom left
		shape[4].position = { 0.f, -30.f };  // Close loop

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

	
	void update(float deltaTime) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
			angle -= TURN_SPEED * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
			angle += TURN_SPEED * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
			float radians = (angle - 90.f) * (PI / 180.f);

			position.x += cos(radians) * PLAYER_SPEED * deltaTime;
			position.y += sin(radians) * PLAYER_SPEED * deltaTime;

		}

	}
	

	/**
	 * @brief Draws the player ship to the given target
	 * 
	 * Applies a transformation to position and rotates without modifying the shape
	 * 
	 * @param target The SFML render target to draw to
	 */
	void Draw(sf::RenderTarget& target) {
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

private:
	sf::VertexArray shape;
	sf::Vector2f position;
	float angle;
	
};

int main() {
	sf::RenderWindow window(sf::VideoMode({ 1200, 900 }), "Asteroids", sf::Style::Close | sf::Style::Titlebar);

	Player player;
	sf::Clock clock;

	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}

 		}

		player.update(deltaTime);

		// Update Game
		window.clear();

	    player.Draw(window);
		// Draw Game
		window.display();
	}

	return 0;
}
