#include <SFML/Graphics.hpp>
#include "player.h"

namespace plr {
    Player::Player(sf::Texture& texture) :
        Collidable(), 
        sprite(texture), 
        health(100), 
        score(0), 
        velocity(0.3f), 
        direction({0, 0}) {
    sf::FloatRect rect = sprite.getGlobalBounds();
    sprite.setOrigin({25.f, 25.f});
    sprite.setPosition({100.f, 100.f});        
    radius = rect.size.y / 2.f;
    center = {rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f};


}
Hitbox Player::getHitbox() const {
    return Hitbox::makeCircle(center, radius);
}
void Player::draw(sf::RenderWindow& win) const {
    if ( health > 0 ) { win.draw(sprite); }
}
void Player::setDirection(sf::Vector2i dir) {
    direction = dir;
}
void Player::move(const sf::Vector2u& winSize) {
    if (health <= 0) { return; }
    if ((direction.x == 0 && direction.y == 0) || health <= 0) {
        return;
    }
    
    sf::Vector2f vec = sprite.getPosition();
    float newX = vec.x + direction.x * velocity;
    float newY = vec.y + direction.y * velocity;
    
    float left = 10.f;
    float right = static_cast<float>(winSize.x / 2) - 10.f;
    float top = 10.f;
    float bottom = static_cast<float>(winSize.y) - 10.f;
    
    if (direction.x == -1 && newX < left) {
        newX = left;
    }
    if (direction.x == 1 && newX > right) {
        newX = right;
    }
    if (direction.y == -1 && newY < top) {
        newY = top;
    }
    if (direction.y == 1 && newY > bottom) {
        newY = bottom;
    }
    
    sprite.setPosition({newX, newY});
    sf::FloatRect rect = sprite.getGlobalBounds();  
    radius = rect.size.y / 2.f;
    center = {rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f};
}
sf::Vector2f Player::getPosition() const {
    sf::Vector2f vec;
    if (health>0) { vec = sprite.getPosition(); }
    else { vec = {0.f, 0.f}; }
    return vec;
}
std::string Player::getHealth() {
    return std::to_string(health);
}
std::string Player::getScore() {
    return std::to_string(score);
}
void Player::setHealth(int x) {
    health = x;
    if (health < 0) { health = 0; }
}
void Player::setScore(int x) {
    score = x;
}
}

