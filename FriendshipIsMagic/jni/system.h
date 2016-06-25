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
        HEALTH = 1 << 7,
        ITEMTYPE = 1 << 8,
        OWNER = 1 << 9,
        SCORE = 1 << 10
    };

    enum Mask
    {
        NONE = 0,
        TAKEN = -1,
        GRAPHICELEMENT = SPRITE | POSITION, // 5
        BULLET = BODY | SPRITE | TIMER | OWNER | POSITION, // 535
        PLAYER = SENSOR | BODY | SPRITE | HEALTH | POSITION | SCORE, // 1167
        BLOC = BODY | SPRITE | POSITION, // 7
        WEAPON = SPRITE | TIMER | WEAPONTYPE | POSITION | DAMAGE, //117
        ITEM = SPRITE | TIMER | POSITION | ITEMTYPE | BODY // 279
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
