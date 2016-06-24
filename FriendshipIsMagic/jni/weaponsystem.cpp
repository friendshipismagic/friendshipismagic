#include "weaponsystem.h"
#include "world.h"

WeaponSystem::WeaponSystem(World* world, State::Context context)
: System(world, context)
{

}

void WeaponSystem::update(sf::Time dt)
{

}

std::string WeaponSystem::getWeaponType(Entity entity)
{
    assert(mWeaponTypes.find(entity) != mWeaponTypes.end());
    return mWeaponTypes[entity];
}

void WeaponSystem::insertWeaponType(Entity entity, std::string weaponType)
{
    if (mWeaponTypes.find(entity) == mWeaponTypes.end())
        mWeaponTypes.insert(std::make_pair(entity, weaponType));
    else
        mWeaponTypes[entity] = weaponType;
}

void WeaponSystem::deleteWeaponType(Entity entity)
{
    if (mWeaponTypes.find(entity) != mWeaponTypes.end())
        mWeaponTypes.erase(entity);
}

int WeaponSystem::getDamage(Entity entity)
{
    assert(mDamages.find(entity) != mDamages.end());
    return mDamages[entity];
}

void WeaponSystem::insertDamage(Entity entity, int damage)
{
    if (mDamages.find(entity) == mDamages.end())
        mDamages.insert(std::make_pair(entity, damage));
    else
        mDamages[entity] = damage;
}

void WeaponSystem::deleteDamage(Entity entity)
{
    if(mDamages.find(entity) != mDamages.end())
        mDamages.erase(entity);
}
