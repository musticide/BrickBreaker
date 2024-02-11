#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!", sf::Style::None | sf::Style::Close);

    sf::RectangleShape player(*new sf::Vector2f(100.f, 20.f));
    player.setOrigin(50.f, 20.f);

    sf::Vector2f playerPos(200.f, 300.f);

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerPos.x -= .5f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerPos.x += .5f;
        }

        // moving the shape

        playerPos.y += .5f;

        // world bounds collision
        // Right
        if (player.getPosition().x > window.getSize().x - (player.getSize().x / 2)) {
            playerPos.x = window.getSize().x - (player.getSize().x / 2);
        }
        // Left
        if (player.getPosition().x < (player.getSize().x / 2)) {
            playerPos.x = (player.getSize().x / 2);
        }
        // Top
        if (player.getPosition().y < (player.getSize().y / 2)) {
            playerPos.y = (player.getSize().y / 2);
        }
        // Bottom
        if (player.getPosition().y > window.getSize().y - (player.getSize().y / 2)) {
            playerPos.y = window.getSize().y - (player.getSize().y / 2);
        }

        player.setPosition(playerPos);

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
