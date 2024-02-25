#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdio>

#define WIDTH 1280
#define HEIGHT 720
#define FRAMERATE 144

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Brick Breaker", sf::Style::None | sf::Style::Close);
    window.setFramerateLimit(FRAMERATE);
    float targetFrameTime = 1.f / FRAMERATE;

    // player stuff----------------------------------------------------------------------
    sf::RectangleShape player(sf::Vector2f(WIDTH * 0.078f, HEIGHT * 0.028f));

    sf::Vector2f playerPos(WIDTH * .5f - (player.getSize().x * .5f), window.getSize().y - player.getSize().y - 10);
    player.setPosition(playerPos);

    float playerAcc = 0;
    float playerFriction = .1f;
    int moveDir = 0;

    sf::Vector2f playerVelocity(0, 0);

    // ball stuff ------------------------------------------------------------------------
    float ballDiam = HEIGHT * 0.028f;
    sf::CircleShape ball(ballDiam * .5f);
    ball.setOrigin(ballDiam, ballDiam);
    ball.setFillColor(sf::Color::Yellow);
    ball.setPosition(WIDTH * .5f - (player.getSize().x * .5f), window.getSize().y - player.getSize().y - 10);
    // ball.setPosition(0, 0);

    sf::Vector2f ballVelocity(0, 9.8f);
    // sf::Vector2f ballVelocity(0, 0);

    // Time-------------------------------------------------------------------------------
    sf::Clock clock;

    // MAIN LOOP--------------------------------------------------------------------------
    while (window.isOpen()) {

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        // Time Handling------------------------------------------------------------------
        sf::Time elapsedTime = clock.restart();
        float deltaTime = elapsedTime.asSeconds();
        deltaTime = std::max(deltaTime, targetFrameTime);

        // moving the player--------------------------------------------------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerAcc += 10;
            moveDir = -1;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerAcc += 10;
            moveDir = 1;
        } else {
            playerAcc = 0;
            moveDir = 0;
        }

        playerVelocity.x += playerAcc * moveDir * deltaTime;
        playerVelocity.x -= playerVelocity.x * playerFriction;

        player.move(playerVelocity);

        // world bounds collision for player---------------------------------------------
        // Right
        if (player.getSize().x + player.getPosition().x + playerVelocity.x > window.getSize().x) {
            player.setPosition(window.getSize().x - player.getSize().x, player.getPosition().y);
            playerVelocity.x *= -1;
        }
        // Bottom
        if (player.getSize().y + player.getPosition().y + playerVelocity.y > window.getSize().y) {
            player.setPosition(player.getPosition().x, window.getSize().y - player.getSize().y);
        }
        // Left
        if (player.getPosition().x + playerVelocity.x < 0) {
            player.setPosition(0, player.getPosition().y);
            playerVelocity.x *= -1;
        }
        // Top
        if (player.getPosition().y + playerVelocity.y < 0) {
            player.setPosition(player.getPosition().x, 0);
        }

        //-------------------------------------------------------------------------------

        // Ball bounds collision---------------------------------------------------------
        // Right
        if (ballDiam + ball.getPosition().x + ballVelocity.x > window.getSize().x) {
            ball.setPosition(window.getSize().x - ballDiam, ball.getPosition().y);
            ballVelocity.x *= -1;
        }
        // Bottom
        if (ballDiam + ball.getPosition().y > window.getSize().y) {
            // ball.setPosition(ball.getPosition().x, window.getSize().y - ballDiam);
            // ballVelocity.y *= -1;

            //////////////////////////////////////////////////////////
            //--------------------GAME OVER-------------------------//
            //////////////////////////////////////////////////////////
        }
        // Left
        if (ball.getPosition().x + ballVelocity.x < 0) {
            ball.setPosition(0, ball.getPosition().y);
            ballVelocity.x *= -1;
        }
        // Top
        if (ball.getPosition().y + ballVelocity.y < 0) {
            ball.setPosition(ball.getPosition().x, 0);
            ballVelocity.y *= -1;
        }
        // ball player collision---------------------------------------------------------
        if (ball.getPosition().y + ball.getRadius() > player.getPosition().y
            && ball.getPosition().y + ball.getRadius() < player.getPosition().y + player.getSize().y
            && ball.getPosition().x + ball.getRadius() > player.getPosition().x
            && ball.getPosition().x + ball.getRadius() < player.getPosition().x + player.getSize().x) {
            ball.setPosition(ball.getPosition().x, player.getPosition().y - ball.getRadius());
            ballVelocity.x *= -1;
            ballVelocity.y *= -1;
            // ballVelocity.x *= playerVelocity.x;
            // ballVelocity.y *= playerVelocity.y;
        }

        // if (ball.getPosition().y + ball.getLocalBounds().height > window.getSize().y) {
        //     ball.setPosition(ball.getPosition().x, window.getSize().y - ball.getLocalBounds().height);
        // }

        ball.move(ballVelocity);

        // draw shape
        window.clear();
        if (window.hasFocus()) {
            player.setFillColor(sf::Color(65, 105, 255, 255));
        } else {
            player.setFillColor(sf::Color(65, 105, 255, 100));
        }
        window.draw(player);
        window.draw(ball);
        window.display();
    }

    return 0;
}
