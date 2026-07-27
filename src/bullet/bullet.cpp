#include <SFML/Graphics.hpp>

#include "bullet.h"

namespace blt {
Bullet::Bullet(sf::Texture& texture, const plr::Player& player) :
        Collidable(),
        sprite(texture),
        velocity(40.f),
        isAlive(false),
        direction({1, 0})   {
            sprite.setOrigin({25.f, 25.f});
            sprite.setPosition(player.getPosition());
            sf::FloatRect rect = sprite.getGlobalBounds();
            radius = rect.size.y / 2;
            center = {rect.position.x, rect.position.y};
        }
Hitbox Bullet::getHitbox() const {
        return Hitbox::makeCircle(center, radius);
}
void Bullet::draw(sf::RenderWindow& win) {
        if (isAlive) { win.draw(sprite); }
}
void Bullet::move(const sf::Vector2u& winSize) {
        if (!isAlive) { return; }
        if (sprite.getPosition().x >= winSize.x -5) { isAlive = false; }
        else { sprite.setPosition({direction.x * velocity, 0}); }
}

}
