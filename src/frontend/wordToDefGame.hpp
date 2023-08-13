#ifndef WORD_TO_DEF_GAME_HPP
#define WORD_TO_DEF_GAME_HPP

#include "button.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>
#include <iostream>

class WordToDefGame : public sf::Drawable
{
private:
    sf::Font font;
    sf::Text question, scoreText, counterText;

    int counter, score, maxCounter;

    Button *quit;

    std::vector<sf::Text *> keywords;
    std::vector<std::vector<Button *>> definitions;

public:
    // constructors
    WordToDefGame(std::vector<std::string> &keywordStr, std::vector<std::vector<std::string>> &definitionStr);
    ~WordToDefGame();

    // getters
    sf::Font getFont();
    std::vector<sf::Text *> getKeywordsRef();
    std::vector<std::vector<Button *>> getDefinitionsRef();
    int getScore();
    int getCounter();

    // setters
    void setFont();
    void setUtilityTexts(); // score and counter
    void setButton();
    void setMetric(); // counter and score set to 0, max counter set to size of keywordStr
    void setQuestion(std::vector<std::string> &keywordStr);
    void setAns(std::vector<std::vector<std::string>> &definitionsStr);

    void updateScores(int scoreChange);
    void updateCounter(int nextCount);
    void centerKeyword(sf::Text *keyword);
};

#endif