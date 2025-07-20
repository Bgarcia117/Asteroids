#include <iostream>
#include <SFML/Graphics.hpp>
#include "global.h"
#include "game.h"
#include "physics.h"

int main() {
	sf::RenderWindow window(sf::VideoMode({
		                    static_cast<unsigned int>(SCREEN_WIDTH), static_cast<unsigned int>(SCREEN_HEIGHT)}), 
		                    "Asteroids", sf::Style::Close | sf::Style::Titlebar);

	sf::Clock clock;

	// Vertex Arrays to store the line strips
	sf::VertexArray poly1(sf::PrimitiveType::LineStrip);
	sf::VertexArray poly2(sf::PrimitiveType::LineStrip);

	// Tracks which polygon is being drawn or if in test mode
	enum { POLY_1, POLY_2, TEST } state = POLY_1;

	// Game::begin();

	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			} 

			else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
					sf::Vector2f pos = (sf::Vector2f)sf::Mouse::getPosition(window);

					if (state == POLY_1) {
						poly1.append(sf::Vertex(pos, sf::Color::White));
					}
					else if (state == POLY_2) {
						poly2.append(sf::Vertex(pos, sf::Color::White));
					}
				}
			}

			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
					if (state == POLY_1 && poly1.getVertexCount() > 0) {
						// Close polygon 1 and move on to polygon 2
						state = POLY_2;
						poly1.append(poly1[0]);
					}
					else if (state == POLY_2 && poly2.getVertexCount() > 0) {
						// Close polygon 2 and enters test mode
						state = TEST;
						poly2.append(poly2[0]);

						if (physics::intersects(poly1, poly2)) {
							std::cout << "Intersects!" << std::endl;
						}
						else {
							std::cout << "Does not!" << std::endl;
						}
					}
					else if (state == TEST) {
						// Reset everything: Clear both polygons
						state = POLY_1;
						poly1.clear();
						poly2.clear();
					}

					// Note: Spacebar does nothing if no vertices are drawn
				}
			}

 		}

		// Game::update(window, deltaTime);
		window.clear();

		window.draw(poly1);
		window.draw(poly2);
		window.display();
	}

	return 0;
}
