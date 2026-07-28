#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>
#include <vector>
#include <filesystem>

#include "../player/player.h"
#include "../bullet/bullet.h"

int main () {

    // Make
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "SFML_Shooter", sf::Style::Close);
    sf::Texture playerTexture, bulletTexture;
    sf::Font fontJet("/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf");
    sf::Text score(fontJet);
    sf::Text health(fontJet);
    sf::Clock moveClock, shootClock;
    std::vector<std::unique_ptr<blt::Bullet>> bullets;

    // Error
    if (!playerTexture.loadFromFile("asset/player.png")) {return 0;}
    if (!bulletTexture.loadFromFile("asset/body.png")) {return 0;}
    
    // Inicial
    plr::Player player(playerTexture);
    for (int i = 0; i < 15; ++i) {
        bullets.push_back(std::move(std::make_unique<blt::Bullet>(bulletTexture, player)));
    }   
    float moveInterval = 0.3f;
    float shootInterval = 0.1f;
    score.setString("100");
    score.setCharacterSize(50);
    score.setFillColor(sf::Color::Black);
    score.setOrigin({0.f, 25.f});
    score.setPosition({window.getSize().x / 2.f, 35.f});
    health.setString("0");
    health.setCharacterSize(50);
    health.setFillColor(sf::Color::Black);
    health.setOrigin({0.f, 25.f});
    health.setPosition({10.f, window.getSize().y - 35.f});

    // Main code    
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        sf::Vector2i dir = {0, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            dir.y = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            dir.y = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            dir.x = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            dir.x = 1; 
        }

        player.setDirection(dir);
        player.move(window.getSize());

        for (auto& z : bullets) { 
            z->move(window.getSize()); 
        }

        if (moveClock.getElapsedTime().asSeconds() >= moveInterval) {
            health.setString(player.getHealth());
            moveClock.restart();
        }

        if (shootClock.getElapsedTime().asSeconds() >= shootInterval) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                for (auto& b : bullets) { 
                    if (!b->is_alive()) { 
                        b->setAlive(true, player.getPosition());
                        break;
                    }
                }
            }
            shootClock.restart();
        }

        window.clear(sf::Color::White);
        player.draw(window);
        for (auto& z : bullets) { 
            z->draw(window); 
        }
        window.draw(health);
        window.display();
    }

    return 0;
}
