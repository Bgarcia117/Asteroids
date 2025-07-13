#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

int main() {
	sf::RenderWindow window(sf::VideoMode({
		                    static_cast<unsigned int>(SCREEN_WIDTH), static_cast<unsigned int>(SCREEN_HEIGHT)}), 
		                    "Asteroids", sf::Style::Close | sf::Style::Titlebar);

	sf::Clock clock;
	Game::begin();

	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}

 		}

		Game::update(window, deltaTime);

		window.display();
	}

	return 0;
}
