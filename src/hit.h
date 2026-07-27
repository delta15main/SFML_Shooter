#include <SFML/Graphics.hpp>






struct Hitbox {
    sf::Vector2f position;
    float radius;
    static Hitbox makeCircle(const sf::Vector2f center, float rad) {
            return { center, rad };
    }
    bool intersect(const Hitbox& other) const {
        sf::Vector2f delta = position - other.position;
        float distsqr = delta.x * delta.x + delta.y * delta.y;
        float radsum  = radius + other.radius;
        return distsqr < (radsum * radsum);
    }
};
class Collidable {
    public:
        virtual Hitbox getHitbox() const = 0;
};
