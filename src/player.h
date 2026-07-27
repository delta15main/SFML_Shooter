#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "hit.h"

namespace plr {
    class Player : public Collidable {
        private:
            sf::Sprite sprite;
            float radius, velocity;
            sf::Vector2f center;
            sf::Vector2i direction;
            int health;
        public:
            Player(sf::Texture& texture);
            Hitbox getHitbox() const override;
            void draw(sf::RenderWindow& win) const;
            void setDirection(sf::Vector2i dir);
            void move(const sf::Vector2u& winSize);
};
}
