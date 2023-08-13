#include "Component.hpp"

using namespace Frontend;

Component::Component(int n_width, int n_height)
    : is_visible_(1),
      width_(n_width), height_(n_height)
{
    createTexture();
    sprite_.setTexture(getTexture().getTexture());
}

bool Component::isVisible() const
{
    return is_visible_;
}

int Component::getWidth() const
{
    return width_;
}

int Component::getHeight() const
{
    return height_;
}

const sf::Vector2f &Component::getPosition() const
{
    return getSprite().getPosition();
}

void Component::setVisibility(bool n_is_visible)
{
    is_visible_ = n_is_visible;
}

void Component::setWidth(int n_width)
{
    width_ = n_width;
    updateTexture();
}

void Component::setHeight(int n_height)
{
    height_ = n_height;
    updateTexture();
}

void Component::setPosition(int x, int y)
{
    sprite_.setPosition(x, y);
}

void Component::setPosition(const sf::Vector2f &n_pos)
{
    sprite_.setPosition(n_pos);
}

void Component::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(getSprite());
}

void Component::createTexture()
{
    texture_.create(getWidth(), getHeight());
}

void Component::updateTexture()
{
}

const sf::RenderTexture &Component::getTexture() const
{
    return texture_;
}

const sf::Sprite &Component::getSprite() const
{
    return sprite_;
}