#include <SFML/Graphics.hpp>

#include "bullet.h"

namespace blt {
Bullet::Bullet(sf::Texture& texture, const plr::Player& player) :
        Collidable(),
        sprite(texture),
        velocity(0.5f),
        isAlive(false),
        direction({1, 0}) {
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
    
    // Двигаем пулю в направлении
    sf::Vector2f pos = sprite.getPosition();
    pos.x += direction.x * velocity;
    
    // Проверка границ (если вылетела за экран - деактивируем)
    if (pos.x > winSize.x) {
        isAlive = false;
        return;
    }
    
    sprite.setPosition(pos);
    
    // Обновляем hitbox
    sf::FloatRect rect = sprite.getGlobalBounds();
    radius = rect.size.y / 2.f;
    center = rect.position + sf::Vector2f(radius, radius);
}
bool Bullet::is_alive() {
    return isAlive;
}

void Bullet::setAlive(bool A, const sf::Vector2f& pos) {
    isAlive = A;
    sprite.setPosition(pos);
}

}   
