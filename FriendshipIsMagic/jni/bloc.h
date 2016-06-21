#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Bloc
{
    public:
        Bloc(b2World* world, float x, float y, float width, float height, float rotation);
        sf::Vector2f getPos();
        b2Body* getBody();
        void setPos(sf::Vector2f);
    private:
        sf::Vector2f mPos;
        b2Body* mBody;
};
