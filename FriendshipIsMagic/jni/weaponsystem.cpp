#include "weaponsystem.h"
#include "world.h"

WeaponSystem::WeaponSystem(World* world, State::Context context)
: System(world, context)
{

}

void WeaponSystem::update(sf::Time dt)
{

}

std::string WeaponSystem::getWeaponType(int entity)
{
    return mWeaponTypes[entity];
}

void WeaponSystem::insertWeaponType(int entity, std::string weaponType)
{
    mWeaponTypes.insert(std::make_pair(entity, weaponType));
}

void WeaponSystem::deleteWeaponType(int entity)
{
    mWeaponTypes.erase(entity);
}

int WeaponSystem::getDamage(int entity)
{
    return mDamages[entity];
}

void WeaponSystem::insertDamage(int entity, int damage)
{
    mDamages.insert(std::make_pair(entity, damage));
}

void WeaponSystem::deleteDamage(int entity)
{
    mDamages.erase(entity);
}
