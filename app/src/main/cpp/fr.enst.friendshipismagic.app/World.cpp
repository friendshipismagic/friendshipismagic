#include "World.hpp"

World::World(State::Context* context)
: mSystems()
{
    graphics = new GraphicSystem(context);
    mSystems.push_back(graphics);
}

void World::update(sf::Time dt)
{
    for(auto itr = mSystems.rbegin(); itr != mSystems.rend(); ++itr)
    {
        (*itr)->update(dt);
    }
}

void World::draw()
{
    graphics->draw();
}
