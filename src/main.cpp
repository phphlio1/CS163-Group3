#include "frontend/header.hpp"
#include <iostream>

int main()
{
    Header header;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    // Game game;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        header.update(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));

        window.draw(header);

        window.display();
    }

    return 0;
}