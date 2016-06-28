#include "aisystem.h"
#include "../core/world.h"

AISystem::AISystem(World* world, State::Context context)
: System(world, context)
, mAI()
, action(AiInterface::Action::still)
, mMatrix(std::vector<char>({'E'}), 1)
{

}

void AISystem::update(sf::Time dt)
{
    action = mAI.giveOrder(1, 0, 0, 800, 200, mMatrix);
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
