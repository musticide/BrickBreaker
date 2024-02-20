#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>

#define WIDTH 1280
#define HEIGHT 720
#define FRAMERATE 144

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Brick Breaker", sf::Style::None | sf::Style::Close);
    window.setFramerateLimit(FRAMERATE);
    float targetFrameTime = 1.f/FRAMERATE;

    sf::RectangleShape player(*new sf::Vector2f(100.f, 20.f));

    sf::Vector2f playerPos(200.f, 300.f);

    sf::Vector2f playerVelocity(0, 0);

    sf::Clock clock;

    while (window.isOpen()) {

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        //Time Handling------------------------------------------------------------------
        sf::Time elapsedTime = clock.restart();
        float deltaTime = elapsedTime.asSeconds();
        deltaTime = std::min(deltaTime, targetFrameTime);

        // moving the shape--------------------------------------------------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerPos.x -= 100.f * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerPos.x += 100.f * deltaTime;
        }

        // gravity
        playerPos.y += 980.f* deltaTime;

        // world bounds collision
        // Right
        if (player.getSize().x + player.getPosition().x > window.getSize().x) {
            playerPos.x = window.getSize().x - player.getSize().x;
        }
        // Bottom
        if (player.getSize().y + player.getPosition().y > window.getSize().y) {
            playerPos.y = window.getSize().y - player.getSize().y;
        }
        // Left
        if (player.getPosition().x < 0) {
            playerPos.x = 0;
        }
        // Top
        if (player.getPosition().y < 0) {
            playerPos.y = 0;
        }

        player.setPosition(playerPos);
        //-------------------------------------------------------------------------------

        // draw shape
        window.clear();
        if (window.hasFocus()) {
            player.setFillColor(sf::Color(65, 105, 255, 255));
        } else {
            player.setFillColor(sf::Color(65, 105, 255, 100));
        }
        window.draw(player);
        window.display();
    }

    return 0;
}
