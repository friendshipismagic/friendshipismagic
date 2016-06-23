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
        TIMER = 1 << 4,
        DAMAGE = 1 << 5,
        WEAPONTYPE = 1 << 6,
        HEALTH = 1 << 7
    };

    enum Mask
    {
        NONE = 0,
        BULLET = BODY | SPRITE | TIMER | DAMAGE,
        PLAYER = SENSOR | BODY | SPRITE | HEALTH,
        BLOC = BODY | SPRITE,
        WEAPON = SPRITE | TIMER | WEAPONTYPE,
        ITEM = SPRITE | TIMER,
        WEAPONITEM = SPRITE | BODY | TIMER | WEAPONTYPE
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
