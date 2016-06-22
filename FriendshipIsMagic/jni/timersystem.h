#pragma once
#include <SFML/Graphics.hpp>
#include "system.h"
#include "state.h"
#include "systemprovider.h"

class World;

class TimerSystem: public System
{
    public:

        TimerSystem(World* world, State::Context context);
        void update(sf::Time dt);

        void insertTimer(int entity, float time);

        void deleteTimer(int entity);

    private:

        State::Context mContext;
        World* mWorld;

        std::map<int, sf::Time> mTimes;
        std::map<int, sf::Time> mCurrentTimers;
        std::vector<int> mTimersToDestroy;

};
