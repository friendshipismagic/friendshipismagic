#include "timersystem.h"
#include "world.h"

TimerSystem::TimerSystem(World* world, State::Context context)
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

    for (int j : mTimersToCall)
    {
        mGameWorld->sigTimerCall(j);
        mCurrentTimers.erase(j);
    }

    mTimersToCall.clear();
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

void TimerSystem::timerOn(int entity)
{
    mCurrentTimers.insert(std::make_pair(entity, sf::Time::Zero));
}
