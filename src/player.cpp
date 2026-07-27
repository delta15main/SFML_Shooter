#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "player.h"
#include "hit.h"

namespace plr {
    Player::Player(sf::Texture& texture) : Collidable(), sprite(texture), health(100), velocity(10.f), direction({0, 0}) {
    sf::FloatRect rect = sprite.getGlobalBounds();
    radius = rect.size.y / 2.f;
    center = {rect.position.x, rect.position.y};
}
Hitbox Player::getHitbox() const {
    return Hitbox::makeCircle(center, radius);
}
void Player::draw(sf::RenderWindow& win) const {
    win.draw(sprite);
}
void Player::setDirection(sf::Vector2i dir) {
    direction = dir;
}
void Player::move() {
    sprite.setPosition({direction.x * velocity, direction.y * velocity});
}
}

