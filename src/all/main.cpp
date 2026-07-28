#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <memory>
#include <utility>
#include <vector>
#include <filesystem>

#include "../player/player.h"
#include "../bullet/bullet.h"
#include "../enemy/enemy.h"

int main () {

    // Make
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML_Shooter", sf::Style::Close);
    sf::Texture playerTexture, bulletTexture, enemyTexture;
    sf::Font fontJet("/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf");
    sf::Text score(fontJet);
    sf::Text lose(fontJet);
    sf::Text health(fontJet);
    sf::Text bulletT(fontJet);
    sf::Clock moveClock, shootClock, enemyClock, endClock, damagedClock;
    std::vector<std::unique_ptr<blt::Bullet>> bullets;
    std::vector<std::unique_ptr<enm::Enemy>> enemies;
    bool isLose, isDamaged;
    uint bullet;

    // Error
    if (!playerTexture.loadFromFile("asset/samsalet.png")) {return 0;}
    if (!bulletTexture.loadFromFile("asset/pistol.png")) {return 0;}
    if (!enemyTexture.loadFromFile("asset/steroid.png")) {return 0;}
    
    // Inicial
    plr::Player player(playerTexture);
    for (int i = 0; i < 20; ++i) { bullets.push_back(std::move(std::make_unique<blt::Bullet>(bulletTexture, player))); }   
    for (int i = 0; i < 4; ++i) { enemies.push_back(std::move(std::make_unique<enm::Enemy>(enemyTexture, fontJet))); }
    float moveInterval = 0.3f;
    float shootInterval = 0.1f;
    float spawnEnemy = 0.5f;
    isLose = false;
    isDamaged = false;
    bullet = bullets.size();
    player.setHealth(100);
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
    lose.setString("Game Over!!!");
    lose.setCharacterSize(70);
    lose.setFillColor(sf::Color::Red);
    lose.setPosition({-200.f, -200.f});
    bulletT.setPosition({ 150.f, window.getSize().y - 65.f });
    bulletT.setFillColor(sf::Color::Red);
    bulletT.setCharacterSize(50);
    bulletT.setString(std::to_string(bullet));

    // Main code    
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Move
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
        for (auto& z : bullets) { z->move(window.getSize()); }
        for (auto& z : enemies) { z->move(window.getSize()); }

        // Text info
        if (moveClock.getElapsedTime().asSeconds() >= moveInterval) {
            health.setString(player.getHealth());
            score.setString(player.getScore());
           
           
           
           
           
           
           
            moveClock.restart();
        }
        if (isDamaged && damagedClock.getElapsedTime().asSeconds() > 3) {
            isDamaged = false;
        }

        // Shooting
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

        // Enemy spawn
        if (enemyClock.getElapsedTime().asSeconds() >= spawnEnemy) {
            for (auto& e : enemies) {
                if (!e->is_alive()) {
                    e->setAlive(true, window.getSize());
                    break;
                }
            }
            enemyClock.restart();
        }

        // Enemy defeat
        for (auto& b : bullets) {
            if (!b->is_alive()) { continue; }
            for (auto& e : enemies) {
                if (!e->is_alive()) { continue; }
                if (e->getHealth() <= 0) {
                    e->setAlive(false, window.getSize());
                    player.setScore(std::stoi(player.getScore()) + 5);
                    continue;
                }
                if (b->getHitbox().intersect(e->getHitbox())) {
                    b->setAlive(false, player.getPosition());
                    e->setHealth(e->getHealth() - 2);
                    player.setScore(std::stoi(player.getScore()) + 2);
                }
            }
        }

        // Player defeat
        if (!isDamaged && std::stoi(player.getHealth()) > 0) {
            for (auto& e : enemies) {
                if (!e->is_alive()) { continue; }
                if (player.getHitbox().intersect(e->getHitbox())) {
                    player.setHealth(std::stoi(player.getHealth()) - 20);
                    isDamaged = true;
                    damagedClock.restart(); 
                    
                    if (std::stoi(player.getHealth()) <= 0) {
                        isLose = true;
                        lose.setPosition({window.getSize().x / 6.f, window.getSize().y / 2.f});
                        endClock.restart();
                    }
                    break;
                }
            }
        }
        
        // Draw
        if (endClock.getElapsedTime().asSeconds() >= 2 && isLose == true) {
            window.close();
        }
        bullet = 0;                                      
        for (const auto& b : bullets) { if (b->is_alive()) { bullet++; } }
        bulletT.setString(std::to_string(bullet));


        window.clear(sf::Color::White);
        player.draw(window);
        for (auto& z : bullets) { z->draw(window); }
        for (auto& z : enemies) { z->draw(window); }
        window.draw(health);
        window.draw(score);
        window.draw(lose);
        window.draw(bulletT);
        window.display();
    }

    return 0;
}
