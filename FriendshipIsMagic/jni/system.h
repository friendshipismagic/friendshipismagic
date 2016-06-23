#pragma once
#include <SFML/System.hpp>
#include "state.h"

class World;

namespace Systems
{
    enum Component
    {
        POSITION = 1 << 0,
        BODY = 1 << 1,
        SPRITE = 1 << 2,
        SENSOR = 1 << 3,
        TIMER = 1 << 4
    };

    enum Mask
    {
        NONE = 0,
        PHYSIC = POSITION | BODY,
        GRAPHIC = POSITION | SPRITE,
        BULLET = BODY | SPRITE | TIMER,
        PLAYER = SENSOR | BODY | SPRITE,
        BLOC = BODY | SPRITE,
        MONSTER = BODY | SPRITE | POSITION
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
