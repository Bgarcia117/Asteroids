#include "bullet.h"
#include "game.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) :
	Entity(position, 0.f), shape(1.f), direction(direction), lifetime(BULLET_LIFE) {

}

void Bullet::update(float deltaTime) override {
	lifetime -= deltaTime;
	position += direction * BULLET_SPEED * deltaTime;

	if (lifetime <= 0.f) {
		Game::toRemoveList.push_back(std::find(entities.begin(), entities.end(), this));
		// delete this;
	}
}

void Bullet::render(sf::RenderTarget& target) override {
	target.draw(shape, sf::Transform().translate(position));
}

