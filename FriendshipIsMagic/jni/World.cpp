#include "world.hpp"
#include "physicsystem.h"

World::World(State::Context* context)
: mSystems()
, right(false)
, left(false)
, x(0)
{
    physics =  new PhysicSystem(context);
    mSystems.push_back(physics);

    graphics = new GraphicSystem(context, physics);
    mSystems.push_back(graphics);

    graphics->setPositionProvider(physics->getPositionProvider());
}

void World::update(sf::Time dt)
{
    physics->mRight = right;
    physics->mLeft = left;
    physics->mJump = jump;

    for(auto itr = mSystems.rbegin(); itr != mSystems.rend(); ++itr)
    {
        (*itr)->update(dt);
    }
}

void World::draw()
{
    graphics->draw();
}

void World::setRight(bool b)
{
    right = b;
}

void World::setLeft(bool b)
{
    left = b;
}
