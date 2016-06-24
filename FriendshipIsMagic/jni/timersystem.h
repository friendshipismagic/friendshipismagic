#pragma once
#include <SFML/Graphics.hpp>
#include "system.h"
#include "state.h"
#include "systemprovider.h"
#include "entity.h"

class World;

class TimerSystem: public System
{
    public:

        TimerSystem(World* world, State::Context context);
        void update(sf::Time dt);

        void insertTimer(Entity entity, float time);
        void deleteTimer(Entity entity);
        void timerOn(Entity entity);

    private:

        std::map<Entity, sf::Time> mTimes;
        std::map<Entity, sf::Time> mCurrentTimers;
        std::vector<Entity> mTimersToCall;

};
