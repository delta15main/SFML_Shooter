#include <SFML/Window/WindowEnums.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

int main () {

    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "SFML_Shooter", sf::Style::Close);



    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {

        }
        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}
