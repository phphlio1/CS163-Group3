#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "button.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>
#include <iostream>

class WordToDefGame : public sf::drawable
{
private:
    sf::Font font;
    sf::Text question, scoreText, counterText;

    int counter, score, maxCounter;

    Button *quit;

    std::vector<sf::Text *> keywords;
    std::vector<std::vector<Button *>> definitions;

    void setFont();
    void setUtilityTexts(); // score and counter
    void setButton();
    void setMetric(); // counter and score set to 0, max counter set to size of keywordStr
    void setQuestion(std::vector<std::string> &keywordStr);
    void setAns(std::vector<std::vector<std::string>> &definitionsStr);

public:
    // constructors
    WordToDefGame(std::vector<std::string> &keywordStr, std::vector<std::vector<std::string>> &definitionStr);
    ~WordToDefGame();

    // getters
    sf::Font getFont() { return font; }
    std::vector<sf::Text *> getKeywordsRef() { return keywords; }
    std::vector<std::vector<sf::Text *>> getDefinitionsRef { return definitions; }
    int getScore() { return score; }
    int getCounter() { return counter; }

    void updateScores(int scoreChange);
    void updateCounter(int nextCount);
    void centerKeyword(sf::Text *keyword);
}

#endif