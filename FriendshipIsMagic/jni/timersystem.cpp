#include "timersystem.h"
#include "world.h"

TimerSystem::TimerSystem(World* world, State::Context context)
: System(world, context)
{

}

void TimerSystem::update(sf::Time dt)
{
    for (std::pair<const int, sf::Time> timer : mCurrentTimers)
    {
        mCurrentTimers[timer.first] += dt;

        if (mCurrentTimers[timer.first].asSeconds() > mTimes[timer.first].asSeconds())
        {
            mTimersToDestroy.push_back(timer.first);
        }
    }

    for (int j : mTimersToDestroy)
    {
        mGameWorld->sigDestroyEntity(j);
    }

    mTimersToDestroy.clear();
}

void TimerSystem::insertTimer(int entity, float time)
{
    sf::Time t = sf::seconds(time);
    mTimes.insert(std::make_pair(entity, t));
    mCurrentTimers.insert(std::make_pair(entity, sf::Time::Zero));
}

void TimerSystem::deleteTimer(int entity)
{
    mTimes.erase(entity);
    mCurrentTimers.erase(entity);
}
