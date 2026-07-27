#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../player/player.h"
#include "../bullet/bullet.h"

int main () {

    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "SFML_Shooter", sf::Style::Close);
    sf::Texture playerTexture, bulletTexture;
    if (!playerTexture.loadFromFile("../../asset/player.png")) {return 0;}
    if (!bulletTexture.loadFromFile("../../asset/body.png")) {return 0;}
    plr::Player player(playerTexture);
    std::vector<std::unique_ptr<blt::Bullet>> bullets;

    sf::Clock moveClock;
    float moveInterval = 0.1f;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
       sf::Vector2i dir = {0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        dir.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        dir.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        dir.x = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        dir.x = 1; 
    }
    player.setDirection(dir);
    
    if (moveClock.getElapsedTime().asSeconds() >= moveInterval) {
        player.move(window.getSize());
        moveClock.restart();
    }
    

        window.clear(sf::Color::White);
        player.draw(window);
        window.display();
    }

    return 0;
}
