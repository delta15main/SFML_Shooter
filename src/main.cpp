#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "hit.h"
#include "player.h"

int main () {

    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "SFML_Shooter", sf::Style::Close);
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../asset/player.png")) {return 0;}
    plr::Player player(playerTexture);


    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Up) {
                    player.setDirection({0, -1});
                } else if (key->code == sf::Keyboard::Key::Down) {
                    player.setDirection({0, 1});
                } else if (key->code == sf::Keyboard::Key::Left) {
                    player.setDirection({-1, 0});
                } else if (key->code == sf::Keyboard::Key::Right) {
                    player.setDirection({1, 0});
                } else if (key->code == sf::Keyboard::Key::Space) {

                }
            }
        }
        window.clear(sf::Color::White);
        player.draw(window);
        window.display();
    }

    return 0;
}
