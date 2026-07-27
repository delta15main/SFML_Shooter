#pragma once
#include <SFML/Graphics.hpp>

#include "../all/hitbox.h"
#include "../player/player.h"

namespace blt {
class Bullet : public Collidable {
private:
    float radius, velocity;
    sf::Vector2f center;
    sf::Vector2i direction;
    sf::Sprite sprite;
    bool isAlive;

public:
    Bullet(sf::Texture& texture, const plr::Player& player);
    Hitbox getHitbox() const override;
    void draw(sf::RenderWindow& win);
    void move(const sf::Vector2u& winSize);
    bool is_alive();
    void setAlive(bool A, const sf::Vector2f& pos);
};


}
