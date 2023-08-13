#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>

namespace Frontend
{
    class Component : public sf::Drawable
    {
    public:
        Component(int n_width = 0, int n_height = 0);

        virtual void processEvent(const sf::Event &event) = 0;

        bool isVisible() const;
        int getWidth() const;
        int getHeight() const;
        const sf::Vector2f &getPosition() const;

        void setWidth(int n_width);
        void setHeight(int n_height);
        void setPosition(int x, int y);
        void setPosition(const sf::Vector2f &n_pos);
        void setVisibility(bool n_is_visible);

    protected:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual void createTexture();
        virtual void updateTexture();

        const sf::RenderTexture &getTexture() const;
        const sf::Sprite &getSprite() const;

        bool is_visible_;
        int width_, height_;

        sf::RenderTexture texture_;
        sf::Sprite sprite_;
    };
}

#endif