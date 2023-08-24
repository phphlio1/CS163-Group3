#include "frontend/InGame.hpp"
#include "frontend/header.hpp"
#include "frontend/gameMode.hpp"
#include <iostream>

int main()
{
    // std::vector<std::string> keywordStr = {"sequence", "null"};
    // std::vector<std::vector<std::string>> definitionStr = {{"a series of related things or events, or the order in which they follow each other", "to combine things in a particular order, or discover the order in which they are combined", "to discover the order in which nucleotides (= chemical substances) are combined within DNA", "all of the above"}, {"null", "null", "null", "null"}};
    // std::vector<int> ans = {3, 0};

    // std::vector<std::string> key = {"sequence", "happy"};
    // std::vector<std::string> ansStr = {
    //     {"a series of related things or events, or the order in which they follow each other",
    //      "to combine things in a particular order, or discover the order in which they are combined",
    //      "to discover the order in which nucleotides (= chemical substances) are combined within DNA",
    //      "all of the above"},
    //     {"the state of joyfulness",
    //      "what you feel when you failed your test",
    //      "a feeling of nothingness",
    //      "all of the above"}};

    // std::vector<int> ans = {3, 0};

    // std::string key = "to discover the order in which nucleotides are combined within DNA";
    // std::string ans1 = "sequence";
    // std::string ans2 = "sentence";
    // std::string ans3 = "search";
    // std::string ans4 = "none of the above";
    // int ans = 0;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    Frontend::Header header;

    Frontend::InGame game(Frontend::GameMenu::WORD_TO_DEF);
    // game.setVisibility(false);

    // Frontend::GameModeMenu menu;

    // game.setQuestionParams(key, ans1, ans2, ans3, ans4, ans);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (game.isVisible())
                game.processEvent(event);

            header.processEvent(event);

            // if (menu.isVisible())
            //     menu.processEvent(event);
        }
        window.clear(sf::Color::White);

        // if (menu.getCurrentGameMenu() == Frontend::GameMenu::WORD_TO_DEF)
        // {
        //     game.setVisibility(true);
        // }

        // if (!game.isVisible())
        //     menu.setGameMenu(Frontend::GameMenu::GAME_MODE_MENU);

        if (game.isVisible())
            window.draw(game);

        // if (menu.isVisible())
        //     window.draw(menu);

        window.draw(header);

        window.display();
    }

    return 0;
}