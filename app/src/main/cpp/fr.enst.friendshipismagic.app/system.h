#pragma once
#include <SFML/System.hpp>

namespace Systems
{
    enum Mask
    {

    };
};

class System
{
    public:

        void virtual update(sf::Time dt) = 0;

};
