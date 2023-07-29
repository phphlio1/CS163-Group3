#include "button.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    sf::Font font;
    font.loadFromFile("UI/resource/Frank_Ruhl_Libre_font/FrankRuhlLibre-Medium.ttf");

    Button test = Button(15, 45, 300, 50,
                         &font, "sequence", 22, 23, 57, sf::Color::Black,
                         sf::Color::White, sf::Color::Cyan, sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

        test.update(mousePos);

        window.clear();

        window.draw(test);
        window.display();
    }

    return 0;
}