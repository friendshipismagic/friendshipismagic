#pragma once
#include <SFML/System.hpp>
#include "../states/state.h"
//#include "../core/world.h"

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
        SCORE = 1 << 10,
        PADDING = 1 << 11,
		NETWORKID = 1 << 12
    };

    enum Mask
    {
        NONE = 0,
        FOOTSENSOR = SENSOR, // 8
        GRAPHICELEMENT = SPRITE | POSITION, // 5
        HEALTHBAR = GRAPHICELEMENT | PADDING, // 2053
        BULLET = BODY | SPRITE | TIMER | OWNER | POSITION | PADDING, // 2583
        PLAYER = BODY | SPRITE | HEALTH | POSITION | SCORE, // 1159
        BLOC = BODY | SPRITE | POSITION, // 7
        WEAPON = SPRITE | TIMER | WEAPONTYPE | POSITION | DAMAGE | PADDING, // 2165
        ITEM = SPRITE | TIMER | POSITION | ITEMTYPE | BODY, // 279
        MONSTER =  BODY | SPRITE | HEALTH | POSITION | TIMER
    };
};


class System
{
    public:

        System(World* world, State::Context& context)
        : mContext(context)
        , mGameWorld(world){}

        //virtual ~System() = 0;
        void virtual update(sf::Time dt) = 0;

    protected:

        State::Context& mContext;
        World* mGameWorld;

};


