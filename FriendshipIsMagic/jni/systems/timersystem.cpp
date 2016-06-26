#include "timersystem.h"
#include "../core/world.h"

TimerSystem::TimerSystem(World* world, State::Context& context)
: System(world, context)
{

}

void TimerSystem::update(sf::Time dt)
{
    for (auto timer : mCurrentTimers)
    {
        mCurrentTimers[timer.first] += dt;

        //std::cout << mTimes[timer.first].asSeconds() << std::endl;

        if (mCurrentTimers[timer.first].asSeconds() > mTimes[timer.first].asSeconds())
        {
            mTimersToCall.push_back(timer.first);
        }
    }

    for (Entity j : mTimersToCall)
    {
        mGameWorld->sigTimerCall(j);
        mCurrentTimers.erase(j);
    }

    mTimersToCall.clear();
}

void TimerSystem::insertTimer(Entity entity, float time)
{
    sf::Time t = sf::seconds(time);

    if (mTimes.find(entity) == mTimes.end())
        mTimes.insert(std::make_pair(entity, t));
    else
        mTimes[entity] = t;

    if(mCurrentTimers.find(entity) == mCurrentTimers.end())
        mCurrentTimers.insert(std::make_pair(entity, sf::Time::Zero));
    else
        mCurrentTimers[entity] = sf::Time::Zero;
}

void TimerSystem::deleteTimer(Entity entity)
{
    if (mTimes.find(entity) != mTimes.end())
        mTimes.erase(entity);
    if(mCurrentTimers.find(entity) != mCurrentTimers.end())
        mCurrentTimers.erase(entity);
}

void TimerSystem::timerOn(Entity entity)
{
    if(mCurrentTimers.find(entity) == mCurrentTimers.end())
        mCurrentTimers.insert(std::make_pair(entity, sf::Time::Zero));
    else
        mCurrentTimers[entity] = sf::Time::Zero;
}
