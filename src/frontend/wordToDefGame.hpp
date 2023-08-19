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
    std::vector<sf::RectangleShape> ansOutline;

    int counter, score, maxCounter;

    Button *quit;

    std::vector<sf::Text *> keywords;
    std::vector<std::vector<Button *>> definitions;
    std::vector<int> ans;

public:
    // constructors
    WordToDefGame(std::vector<std::string> &keywordStr, std::vector<std::vector<std::string>> &definitionStr, std::vector<int> &randomizedAns);
    ~WordToDefGame();

    // getters
    sf::Font getFont();
    std::vector<sf::Text *> getKeywordsRef();
    std::vector<std::vector<Button *>> getDefinitionsRef();
    std::vector<int> getAns();
    int getScore();
    int getCounter();

    // setters
    void setFont();
    void setUtilityTexts(); // score and counter
    void setButton();
    void setMetric(); // counter and score set to 0, max counter set to size of keywordStr
    void setQuestion(std::vector<std::string> &keywordStr);
    void setOptions(std::vector<std::vector<std::string>> &definitionsStr);
    void setAns(std::vector<int> &randomizedAns);
    void setOutlineAns();

    void updateScores();
    void updateCounter();
    void updateButtons(const sf::Event &event, const sf::Vector2f mousePosRelativeToWindow);
    void highlightAns();
    void centerKeyword(sf::Text *keyword);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif