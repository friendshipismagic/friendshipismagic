#pragma once
#include <SFML/System.hpp>

namespace Systems
{
    enum Component
    {
        NONE = 0,
        POSITION = 1 << 0,
        BODY = 1 << 1,
        SPRITE = 1 << 2

    };

    enum Mask
    {
        PHYSIC = POSITION | BODY,
        GRAPHIC = POSITION | SPRITE,
        BULLET = BODY | SPRITE
    };
};

class System
{
    public:

        void virtual update(sf::Time dt) = 0;

};
