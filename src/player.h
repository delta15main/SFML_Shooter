#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "hit.h"

namespace player {
    class Player : public Collidable {
        private:
            sf::Sprite sprite;
            float radius;
            sf::Vector2f center;
        public:
            Player(sf::Texture& texture, sf::FloatRect& rect) : Collidable(), sprite(texture) {
                radius = rect.size.y / 2.f;
                center = {rect.position.x, rect.position.y};
            }
            Hitbox getHitbox() const override {
                return Hitbox::makeCircle(center, radius);
            }
    };
}
