#include <memory>
#include <random>
#include <SFML/Graphics.hpp>

#include "../all/hitbox.h"
#include "enemy.h"

namespace enm {
    Enemy::Enemy(const sf::Texture& texture, const sf::Font& font) :
    sprite(texture),
    textHealth(font),
    direction({-1, 0}),
    health(10),
    isAlive(false),
    posY(0)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distF(0.1f, 0.3f);
        velocity = distF(gen);

        sf::FloatRect rect = sprite.getGlobalBounds();
        center = {rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f};
        radius = rect.size.x / 2.f;

        textHealth.setCharacterSize(20);
        textHealth.setFillColor(sf::Color::Black);
        textHealth.setOrigin({0.f, 10.f});

    }
    Hitbox Enemy::getHitbox() const {
        return Hitbox::makeCircle(center, radius);
    }
    void Enemy::draw(sf::RenderWindow& win) {
        if ( isAlive ) {
            win.draw(sprite); 
            textHealth.setString(std::to_string(health));
            win.draw(textHealth);
        }
    }
    bool Enemy::is_alive() const {
        return isAlive;
    }
    uint Enemy::getHealth() const {
        return health;
    }
    void Enemy::setHealth(uint x) {
        health = x;
    }
    void Enemy::setAlive(bool x, const sf::Vector2u& winSize) {
        health = 10;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint> distU(0, winSize.y);
        posY = distU(gen);
        isAlive = x;
        sprite.setPosition({winSize.x * 1.f, posY * 1.f});
        sf::FloatRect rect = sprite.getGlobalBounds();
        center = {rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f};
        radius = rect.size.x / 2.f;
        if (x == false) { textHealth.setPosition({-40.f, -40.f}); }
        else { textHealth.setPosition({sprite.getPosition().x - 5.f, sprite.getPosition().y - 15.f}); }
    }
    void Enemy::move(const sf::Vector2u& winSize) {
       if ( !isAlive ) { return; }
       sf::Vector2f tmp = sprite.getPosition();
       if ( tmp.x <= 0.f ) { isAlive = false; return; }
       float newX;
       newX = tmp.x + ( direction.x * velocity );
       sprite.setPosition({newX, posY * 1.f});
       textHealth.setPosition({newX - 10.f, posY - 25.f});
        sf::FloatRect rect = sprite.getGlobalBounds();
        center = {rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f};
        radius = rect.size.x / 2.f;
    }
    

}
