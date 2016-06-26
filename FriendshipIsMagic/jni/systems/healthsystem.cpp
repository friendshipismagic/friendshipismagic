#include "healthsystem.h"
#include "../core/world.h"
#include "../core/player.h"

HealthSystem::HealthSystem(World* world, State::Context& context, GraphicSystem* graphics)
: System(world, context)
, graphics(graphics)
{

}

void HealthSystem::update(sf::Time dt)
{
    for(auto health : mCurrentHealth)
    {
        int currentLife = health.second;

        if(currentLife <= 0)
            mGameWorld->sigDestroyEntity(health.first);

        graphics->setSize(mHealthBarCorrelation[health.first], Player::HealthBarNormalSize*currentLife/Player::NormalMaxLife, 10);
    }
}

int HealthSystem::getCurrentHealth(Entity entity)
{
    assert(mCurrentHealth.find(entity) != mCurrentHealth.end());
    return mCurrentHealth[entity];
}

int HealthSystem::getMaxHealth(Entity entity)
{
    assert(mMaxHealth.find(entity) != mMaxHealth.end());
    return mMaxHealth[entity];
}

void HealthSystem::insertHealth(Entity entity, int health)
{
    if (mMaxHealth.find(entity) == mMaxHealth.end())
        mMaxHealth.insert(std::make_pair(entity, health));
    else
        mMaxHealth[entity] = health;

    if (mCurrentHealth.find(entity) == mCurrentHealth.end())
        mCurrentHealth.insert(std::make_pair(entity, health));
    else
        mCurrentHealth[entity] = health;
}

void HealthSystem::deleteHealth(Entity entity)
{
    if (mMaxHealth.find(entity) != mMaxHealth.end())
        mMaxHealth.erase(entity);

    if (mCurrentHealth.find(entity) != mCurrentHealth.end())
        mCurrentHealth.erase(entity);

    if (mHealthBarCorrelation.find(entity) != mHealthBarCorrelation.end())
        mHealthBarCorrelation.erase(entity);
}

void HealthSystem::addToHealth(Entity entity, int amount)
{
    mCurrentHealth[entity] += amount;
    int maxHealth = mMaxHealth[entity];
    if (mCurrentHealth[entity] > maxHealth)
        mCurrentHealth[entity] = maxHealth;
}

void HealthSystem::insertHealthBar(Entity entityOwner, Entity entityHealthBar)
{
    if (mHealthBarCorrelation.find(entityOwner) == mHealthBarCorrelation.end())
        mHealthBarCorrelation.insert(std::make_pair(entityOwner, entityHealthBar));
    else
        mHealthBarCorrelation[entityOwner] = entityHealthBar;
}
