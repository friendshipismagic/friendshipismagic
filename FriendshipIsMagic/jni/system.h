#pragma once
#include <SFML/System.hpp>

namespace Systems
{
    enum Component
    {
        POSITION = 1,
        BODY = 2,
        SPRITE = 4

    };

    enum Mask
    {
        PHYSIC = POSITION & BODY,
        GRAPHIC = POSITION & SPRITE
    };
};

class System
{
    public:

        void virtual update(sf::Time dt) = 0;

};
