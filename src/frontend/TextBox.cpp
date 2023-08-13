#include "TextBox.hpp"

using namespace Frontend;

const int TextBox::OUTLINE_THICKNESS = -2;
const sf::Color TextBox::GREY = sf::Color(0, 0, 0, 100);

TextBox::TextBox(int n_width, int n_height, int n_margin)
    : width_(n_width), height_(n_height), margin_(n_margin),
      background_color_(sf::Color::White)
{
    createTexture(getWidth(), getHeight());
    sprite_.setTexture(getTexture().getTexture());

    centerText(background_text_);
    centerText(foreground_text_);
    background_text_.setFont(font_);
    foreground_text_.setFont(font_);
    setBackgroundTextColor(GREY); // grey
    setForegroundTextColor(sf::Color::Black);
    setCharacterSize(16);

    setTypingOutlineColor(sf::Color::Green);
    setUntypingOutlineColor(sf::Color::Black);

    updateTexture();
}

void TextBox::processEvent(const sf::Event &event)
{
    auto is_inside = [=](int x, int y) -> bool
    {
        return getSprite().getGlobalBounds().contains(x, y);
    };

    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
        setTypingEnabled(is_inside(event.mouseButton.x, event.mouseButton.y));
        break;

    case sf::Event::TextEntered:
        if (isTyping())
        {
            updateText(event);
        }
        break;

    default:
        break;
    }
}

int TextBox::getWidth() const
{
    return width_;
}

int TextBox::getHeight() const
{
    return height_;
}

int TextBox::getMargin() const
{
    return margin_;
}

int TextBox::getCharacterSize() const
{
    return foreground_text_.getCharacterSize();
}

const sf::String &TextBox::getBackgroundString() const
{
    return background_text_.getString();
}

const sf::String &TextBox::getForegroundString() const
{
    return foreground_text_.getString();
}

const sf::Font &TextBox::getFont() const
{
    return font_;
}

const sf::Color &TextBox::getBackgroundColor() const
{
    return background_color_;
}

const sf::Color &TextBox::getBackgroundTextColor() const
{
    return background_text_.getFillColor();
}

const sf::Color &TextBox::getForegroundTextColor() const
{
    return foreground_text_.getFillColor();
}

const sf::Color &TextBox::getTypingOutlineColor() const
{
    return typing_outline_color_;
}

const sf::Color &TextBox::getUntypingOutlineColor() const
{
    return untyping_outline_color_;
}

bool TextBox::isTyping() const
{
    return is_typing_;
}

void TextBox::setWidth(int n_width)
{
    width_ = n_width;
    updateTexture();
}

void TextBox::setHeight(int n_height)
{
    height_ = n_height;
    updateTexture();
}

void TextBox::setMargin(int n_margin)
{
    margin_ = n_margin;
    updateTexture();
}

void TextBox::setCharacterSize(int size)
{
    foreground_text_.setCharacterSize(size);
    background_text_.setCharacterSize(size);
    updateTexture();
}

void TextBox::setBackgroundString(const sf::String &text)
{
    background_text_.setString(text);
    updateTexture();
}

void TextBox::setForegroundString(const sf::String &text)
{
    foreground_text_.setString(text);
    updateTexture();
}

void TextBox::setFont(const sf::String &filename)
{
    font_.loadFromFile(filename.toAnsiString());
    updateTexture();
}

void TextBox::setBackgroundColor(const sf::Color &color)
{
    background_color_ = color;
    updateTexture();
}

void TextBox::setBackgroundTextColor(const sf::Color &color)
{
    background_text_.setFillColor(color);
    updateTexture();
}

void TextBox::setForegroundTextColor(const sf::Color &color)
{
    foreground_text_.setFillColor(color);
    updateTexture();
}

void TextBox::setTypingOutlineColor(const sf::Color &color)
{
    typing_outline_color_ = color;
    updateTexture();
}

void TextBox::setUntypingOutlineColor(const sf::Color &color)
{
    untyping_outline_color_ = color;
    updateTexture();
}

void TextBox::setTypingEnabled(bool n_is_typing)
{
    is_typing_ = n_is_typing;
    updateTexture();
}

void TextBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(getSprite());
}

void TextBox::createTexture(int width, int height)
{
    texture_.create(getWidth(), getHeight());
}

void TextBox::updateTexture()
{
    texture_.clear(background_color_);

    sf::RectangleShape outline(sf::Vector2f(texture_.getSize()));
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(isTyping() ? getTypingOutlineColor() : getUntypingOutlineColor());
    outline.setOutlineThickness(OUTLINE_THICKNESS);

    const sf::Text &text_display = (isTyping() || getForegroundString().getSize() ? foreground_text_ : background_text_);

    texture_.draw(outline);
    texture_.draw(text_display);

    texture_.display();
}

void TextBox::centerText(sf::Text &text_display)
{
    text_display.setPosition(sf::Vector2f(getMargin(), texture_.getSize().y / 2));
}

const sf::RenderTexture &TextBox::getTexture() const
{
    return texture_;
}

const sf::Sprite &TextBox::getSprite() const
{
    return sprite_;
}

void TextBox::updateText(const sf::Event &event)
{
    if (event.type != sf::Event::TextEntered)
    {
        return;
    }

    switch (event.text.unicode)
    {
    case '\b':
        if (getForegroundString().getSize() > 0)
        {
            setForegroundString(getForegroundString().substring(0, getForegroundString().getSize() - 1));
        }
        break;

    case '\n':
    case '\r':
        break;

    default:
        int character_width = getFont().getGlyph(event.text.unicode,
                                                 getCharacterSize(), 0)
                                  .bounds.width;
        if (foreground_text_.getLocalBounds().width + character_width + foreground_text_.getLetterSpacing() <= getWidth() - 2 * getMargin())
        {
            setForegroundString(getForegroundString() + event.text.unicode);
        }
        break;
    }
    updateTexture();
}