#include "button.hpp"
#include "../UI/SFML/include/SFML/Window.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Font font;
    font.loadFromFile("../UI/resource/FrankRuhlLibre-Black.ttf");

    Button button = Button(15, 45, 300, 50,
                           &font, "sequence", 22, 23, 57, sf::Color::Black,
                           sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        button.update(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
        window.draw(button);
    }

    return 0;
}