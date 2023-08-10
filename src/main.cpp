#include "gameGUI.hpp"
#include <iostream>

int main()
{
    // sf::Font font;
    // sf::Image image;
    // image.loadFromFile("resources/img/word-to-def.png");

    // if (!font.loadFromFile("resources/font/open-sans-hebrew/OpenSansHebrew-Bold.ttf"))
    //     throw std::runtime_error("No font found");

    // sf::Texture wordToDef;
    // wordToDef.loadFromImage(image);
    // sf::Texture defToWord;
    // sf::Texture empty;

    // Button wordToDefBtn = Button(240, 270, 270, 300,
    //                              &font, "Word to Defintion", 24, 264, 537, sf::Color::Black,
    //                              sf::Color::White, sf::Color(215, 215, 215), sf::Color(215, 215, 215));

    Game game;
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
        game.Update(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));

        window.draw(game);
        // window.draw(wordToDefBtn);
        // window.draw(wordToDefBtn.getSprite());
        // window.draw(text);
        // window.draw(sprite);
        window.display();
    }

    return 0;
}