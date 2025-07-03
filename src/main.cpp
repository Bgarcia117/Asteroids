#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player {
public: 
	Player()
		: shape(sf::PrimitiveType::LineStrip, 4), position(500.f, 500.f), angle(45.f) {
		shape[0].position = sf::Vector2f(0.f, -30.f);
		shape[1].position = sf::Vector2f(-30.f, -30.f);
		shape[2].position = sf::Vector2f(0.f, 15.f);
		shape[3].position = sf::Vector2f(30.f, -30.f);

		for (sf::Vertex& vertex : shape) {
			vertex.color = sf::Color::Green;
		}
	}

	void Draw(sf::RenderWindow& window) {
		sf::Transform transform;
		transform.translate(position).rotate(sf::radians(angle));
		window.draw(shape, transform);
	}

private:
	sf::VertexArray shape;
	sf::Vector2f position;
	float angle;
	
};

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Asteroids", sf::Style::Close | sf::Style::Titlebar);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is < sf::Event::Closed) {
				window.close();
			}
 		}

		// Update Game
		window.clear();

		// Draw Game
		window.display();
	}
}
