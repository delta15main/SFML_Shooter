#pragma once
#include <memory>
#include <vector>
#include <future>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

#include "../all/hitbox.h"

namespace enm {
class Enemy : public Collidable {
private:
    sf::Sprite sprite;
    sf::Text textHealth;
    sf::Vector2f center;
    sf::Vector2i direction;
    float velocity, radius;
    uint health, posY;
    bool isAlive;

public:
    Enemy(const sf::Texture& texture, const sf::Font& font);
    Hitbox getHitbox() const override;
    void draw(sf::RenderWindow& win) ;
    void move(const sf::Vector2u& winSize);
    bool is_alive() const;
    uint getHealth() const;
    void setHealth(uint x);
    void setAlive(bool x, const sf::Vector2u& winSize);

    };
}

