#include "frontend/header.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    Header header;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            header.update(event, sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
        }
        window.clear(sf::Color::White);

        window.draw(header);

        window.display();
    }

    return 0;
}