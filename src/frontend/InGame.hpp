#ifndef IN_GAME_HPP
#define IN_GAME_HPP

#include "button.hpp"
#include "gameMode.hpp"
#include "Component.hpp"
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <iostream>

namespace Frontend
{
    class InGame : public Component
    {
    private:
        short unsigned inGameMode;
        sf::Font font;
        sf::Text questionForWordToDef, scoreText, counterText;
        std::vector<sf::RectangleShape> ansOutline;

        sf::RectangleShape header, footer;

        int counter, score, maxCounter;

        sf::Text key, congrats, subCongrats, finalScore;
        Button quit, ans1, ans2, ans3, ans4, home;

        // question params
        std::string keyStr;
        std::vector<std::string> ansStrs;
        int ans;

    public:
        // constructors
        InGame(short unsigned gameMode);
        ~InGame();

        // getters
        sf::Font getFont();
        sf::Text getKeyText();
        int getAns();
        int getScore();
        int getCounter();

        // setters
        void setFont(std::string filename = "resources/font/open-sans-hebrew/OpenSansHebrew-Bold.ttf");
        void setUtilityTexts();   // score and counter
        void setQuestionParams(); // call backend function to update params
        void setButton();
        void setMetric(int startCount = 1, int startScore = 0, int numberOfQuestions = 10);
        void setQuestion();
        void setOutlineAns();
        void setFinalScore();

        void updateScores();
        void updateCounter();
        void highlightAns(bool showAns);
        void centerText(sf::Text &keyword, float y);
        void centerDefinition(sf::Text &definition);

        virtual void processEvent(const sf::Event &event) override;

    protected:
        virtual void updateTexture() override;
    };
}

void setParams(std::string &key_n, std::vector<std::string> &ansStr_n, int &ans_n);

#endif