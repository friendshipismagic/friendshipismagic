#include "healthsystem.h"
#include "world.h"

HealthSystem::HealthSystem(World* world, State::Context context, GraphicSystem* graphics)
: System(world, context)
, graphics(graphics)
{

}

void HealthSystem::update(sf::Time dt)
{
    for(auto health : mCurrentHealth)
    {
        float maxLife = mMaxHealth[health.first];
        int currentLife = health.second;

        if(currentLife <= 0)
            mGameWorld->sigDestroyEntity(health.first);

        graphics->setSize(mHealthBarCorrelation[health.first], 50*currentLife/maxLife, 10);
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

void HealthSystem::insertHealthBar(int entityOwner, int entityHealthBar)
{
    mHealthBarCorrelation.insert(std::make_pair(entityOwner, entityHealthBar));
}
