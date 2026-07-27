#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>
#include <vector>

#include "../player/player.h"
#include "../bullet/bullet.h"

int main () {

    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "SFML_Shooter", sf::Style::Close);
    sf::Texture playerTexture, bulletTexture;
    if (!playerTexture.loadFromFile("../asset/player.png")) {return 0;}
    if (!bulletTexture.loadFromFile("../asset/body.png")) {return 0;}
    plr::Player player(playerTexture);
    std::vector<std::unique_ptr<blt::Bullet>> bullets;
    for (int i = 0; i < 30; ++i) {
        bullets.push_back(std::move(std::make_unique<blt::Bullet>(bulletTexture, player)));
    }

    sf::Clock moveClock;
    float moveInterval = 0.3f;

    while (window.isOpen()) {
        // ========== 1. ОБРАБОТКА СОБЫТИЙ ==========
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Space) {
                    for (auto& b : bullets) { 
                        if (!b->is_alive()) { 
                            b->setAlive(true, player.getPosition());
                            break;
                        }
                    }
                }
            }
        }

        // ========== 2. ОБНОВЛЕНИЕ ИГРЫ (каждый кадр) ==========
        // Читаем состояние клавиш
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

        // Двигаем игрока
        player.setDirection(dir);
        player.move(window.getSize());

        // Двигаем пули (теперь всегда, даже если игрок стоит)
        for (auto& z : bullets) { 
            z->move(window.getSize()); 
        }

        // Таймер (если нужен)
        if (moveClock.getElapsedTime().asSeconds() >= moveInterval) {
            moveClock.restart();
        }

        // ========== 3. ОТРИСОВКА ==========
        window.clear(sf::Color::White);
        player.draw(window);
        for (auto& z : bullets) { 
            z->draw(window); 
        }
        window.display();
    }

    return 0;
}
