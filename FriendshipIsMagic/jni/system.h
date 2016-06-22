#pragma once
#include <SFML/System.hpp>
#include "state.h"

class World;

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

        System(World* world, State::Context context)
        : mContext(context)
        , mGameWorld(world)
        {

        }
        void virtual update(sf::Time dt) = 0;

    protected:

        State::Context mContext;
        World* mGameWorld;

};
