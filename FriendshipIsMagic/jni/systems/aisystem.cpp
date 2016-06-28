#include "aisystem.h"
#include "../core/world.h"

AISystem::AISystem(World* world, State::Context context, PhysicSystem* physics)
: System(world, context)
, mAI()
, action(AiInterface::Action::still)
, mMatrix(std::vector<char>({'E'}), 1)
, mPhysics(physics)
{

}

void AISystem::update(sf::Time dt)
{
    Entity player = mGameWorld->getPlayerID();
    sf::Vector2f pos = mPhysics->getPosition(player);
    for(Entity mob : mMonsters)
    {
        sf::Vector2f mobPos = mPhysics->getPosition(mob);
        action = mAI.giveOrder(1, pos.x, pos.y, mobPos.x, mobPos.y, mMatrix);
        mPhysics->updateMob(action, mob);
    }
}

AiInterface::Action AISystem::getAction()
{
    return action;
}

void AISystem::setMatrix(std::string tile, int n)
{
    std::vector<char> charTile;
    for(unsigned int i = 0; i < tile.size(); i++)
    {
        charTile.push_back(tile[i]);
    }
    mMatrix = Matrix(charTile, n);
}

void AISystem::insertMonster(Entity entity)
{
    mMonsters.insert(entity);
}

void AISystem::deleteMonster(Entity entity)
{
   if (mMonsters.find(entity) != mMonsters.end())
       mMonsters.erase(entity);
}
