#include "itemsystem.h"
#include "../world.h"

ItemSystem::ItemSystem(World* world, State::Context context)
: System(world, context)
{

}

void ItemSystem::update(sf::Time dt)
{

}

ItemType ItemSystem::getType(Entity entity)
{
    if(mTypes.find(entity) == mTypes.end())
        throw std::runtime_error("ItemSystem : Failed to find type of ");
    return mTypes[entity];
}

void ItemSystem::insertType(Entity entity, ItemType type)
{
    if (mTypes.find(entity) == mTypes.end())
        mTypes.insert(std::make_pair(entity, type));
    else
        mTypes[entity] = type;
}

void ItemSystem::deleteType(Entity entity)
{
    if (mTypes.find(entity) != mTypes.end())
        mTypes.erase(entity);
}

ItemType ItemSystem::fromString(std::string type)
{
    if (type.compare("weapon") == 0)
        return ItemType::weapon;
    if (type.compare("swapstuff") == 0)
        return ItemType::swapstuff;
     if (type.compare("heal") == 0)
        return ItemType::heal;
     if (type.compare("increaseMaxLife") == 0)
        return ItemType::increaseMaxLife;

    return ItemType::none;
}
