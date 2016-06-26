#pragma once
#include <SFML/Graphics.hpp>

template <typename Graphic>
class GraphicElement
{
    public:

        void setLayer(int layer);
        int getLayer();
        void setPosition(sf::Vector2f pos);
        sf::Vector2f getPosition();

        void setElement(Graphic* element);
        void draw(sf::RenderWindow* window);
        Graphic* getElement();

    protected:

        int mLayer = 0;
        sf::Vector2f mPos = sf::Vector2f({0,0});
        Graphic* mElement;

};

template <typename Graphic>
Graphic* GraphicElement<Graphic>::getElement()
{
    return mElement;
}

template <typename Graphic>
void GraphicElement<Graphic>::setElement(Graphic* element)
{
    mElement = element;
}

template <typename Graphic>
void GraphicElement<Graphic>::draw(sf::RenderWindow* window)
{
    window->draw(*mElement);
}

template <typename Graphic>
sf::Vector2f GraphicElement<Graphic>::getPosition()
{
    return mPos;
}

template <typename Graphic>
int GraphicElement<Graphic>::getLayer()
{
    return mLayer;
}

template <typename Graphic>
void GraphicElement<Graphic>::setLayer(int layer)
{
    mLayer = layer;
}

template <typename Graphic>
void GraphicElement<Graphic>::setPosition(sf::Vector2f pos)
{
    mPos = pos;
    mElement->setPosition(mPos);
}

using SpriteElement = GraphicElement<sf::Sprite>;
