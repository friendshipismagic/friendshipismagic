#include "healthsystem.h"
#include "world.h"

HealthSystem::HealthSystem(World* world, State::Context context)
: System(world, context)
{

}

void HealthSystem::update(sf::Time dt)
{
    for(auto health : mCurrentHealth)
    {
        if(health.second <= 0)
            mGameWorld->sigDestroyEntity(health.first);
    }
}

int HealthSystem::getCurrentHealth(int entity)
{
    return mCurrentHealth[entity];
}

void HealthSystem::insertHealth(int entity, int health)
{
    mMaxHealth.insert(std::make_pair(entity, health));
    mCurrentHealth.insert(std::make_pair(entity, health));
}

void HealthSystem::deleteHealth(int entity)
{
    mMaxHealth.erase(entity);
    mCurrentHealth.erase(entity);
}

void HealthSystem::addToHealth(int entity, int amount)
{
    mCurrentHealth[entity] += amount;
    int maxHealth = mMaxHealth[entity];
    if (mCurrentHealth[entity] > maxHealth)
        mCurrentHealth[entity] = maxHealth;
}
