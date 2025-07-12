#include <iostream>
#include <numbers>
#include <vector>
#include <list>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

constexpr float PI = 3.14159265f;
constexpr float TURN_SPEED = 200.0f;
constexpr float PLAYER_SPEED = 200.f;
constexpr float SHOOT_DELAY = 0.2f;
constexpr float	BULLET_SPEED = 400.f;
constexpr float BULLET_LIFE = 3.f;

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

std::vector<Entity*> entities;
std::list<std::vector<Entity*>::const_iterator> toRemoveList;
std::list<Entity*> toAddList;

class Bullet : public Entity {
public:
	Bullet(sf::Vector2f position, sf::Vector2f direction) :
		Entity(position, 0.f), shape(1.f), direction(direction), lifetime(BULLET_LIFE) {

	}

	void update(float deltaTime) override {
		lifetime -= deltaTime;
		position += direction * BULLET_SPEED * deltaTime;

		if (lifetime <= 0.f) {
			toRemoveList.push_back(std::find(entities.begin(), entities.end(), this));
			// delete this;
		}
	}

	void render(sf::RenderTarget& target) override {
		target.draw(shape, sf::Transform().translate(position));
	}

private:
	sf::CircleShape shape;
	sf::Vector2f direction;
	float lifetime;
 };



class Player : public Entity {
public: 
	Player()
		: Entity({500.f, 500.f}, 0.f), shape(sf::PrimitiveType::LineStrip, 5), shootTimer() {

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

	
	void update(float deltaTime) override {
		shootTimer -= deltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
			angle -= TURN_SPEED * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
			angle += TURN_SPEED * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
			// Degrees -> Radian Equation: degrees * (PI/180)
			float radians = (angle - 90.f) * (PI / 180.f);

			position.x += cos(radians) * PLAYER_SPEED * deltaTime;
			position.y += sin(radians) * PLAYER_SPEED * deltaTime;

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) && shootTimer <= 0.0f) {
			shootTimer = SHOOT_DELAY;
			float radians = (angle - 90.f) * (PI / 180.f);

			toAddList.push_back(new Bullet(position, sf::Vector2f(cos(radians), sin(radians))));
			std::cout << entities.size() << std::endl;
		}

	}
	

	/**
	 * @brief Draws the player ship to the given target
	 * 
	 * Applies a transformation to position and rotates without modifying the shape
	 * 
	 * @param target The SFML render target to draw to
	 */
	void render(sf::RenderTarget& target) override {
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
	float shootTimer;
	
};

class Asteroid : public Entity {
public:
	Asteroid()
		: Entity({ 600.f, 300.f }, 0.f), shape(sf::PrimitiveType::LineStrip, 12) {

		shape[0].position = { -40.f, 40.f };  
		shape[1].position = { -50.f, 10.f };  
		shape[2].position = { -10.f, -20.f };   
		shape[3].position = { -20.f, -40.f }; 
		shape[4].position = { 10.f, -40.f }; 
		shape[5].position = { 40.f, -20.f };
		shape[6].position = { 40.f, 10.f };
		shape[7].position = { 30.f, 0.f} ;   
		shape[8].position = { 40.f, 20.f };
		shape[9].position = { 20.f, 40.f };
		shape[10].position = { 0.f, 30.f };
		shape[11].position = shape[0].position;

		for (std::size_t i = 0; i < shape.getVertexCount(); ++i) {
			shape[i].color = sf::Color::White;
		}
	}


	void update(float deltaTime) override {


	}

	void render(sf::RenderTarget& target) override {
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

private:
	sf::VertexArray shape;

};

int main() {
	sf::RenderWindow window(sf::VideoMode({ 1200, 900 }), "Asteroids", sf::Style::Close | sf::Style::Titlebar);

	sf::Clock clock;

	entities.push_back(new Player());
	entities.push_back(new Asteroid());

	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}

 		}

		toAddList.clear();
		toRemoveList.clear();

		// Update Game
		window.clear();

		
		for (size_t i = 0; i < entities.size(); i++) {
			entities[i]->update(deltaTime);
			entities[i]->render(window);
		}

		for (const auto& it : toRemoveList) {
			delete* it;
			entities.erase(it);
		}

		for (auto& ptr : toAddList) {
			entities.push_back(ptr);
		}
		
		/*
		for (auto& entity : entities) {
			entity->update(deltaTime);
			entity->render(window);
		}
		*/

		// Draw Game
		window.display();
	}

	return 0;
}
