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
        TAKEN = -1,
        GRAPHICELEMENT = SPRITE | POSITION,
        BULLET = BODY | SPRITE | TIMER | DAMAGE | POSITION,
        PLAYER = SENSOR | BODY | SPRITE | HEALTH | POSITION,
        BLOC = BODY | SPRITE | POSITION,
        WEAPON = SPRITE | TIMER | WEAPONTYPE | POSITION,
        ITEM = SPRITE | TIMER | POSITION,
        WEAPONITEM = SPRITE | BODY | TIMER | WEAPONTYPE | POSITION,
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
