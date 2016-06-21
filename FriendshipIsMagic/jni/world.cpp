#include "World.hpp"
#include "PhysicSystem.h"

World::World(State::Context* context)
: mSystems()
{
    inputs = new InputSystem(context);
    mSystems.push_back(inputs);

    physics =  new PhysicSystem(context, inputs);
    mSystems.push_back(physics);

    graphics = new GraphicSystem(context, physics);
    mSystems.push_back(graphics);

    graphics->setPositionProvider(physics->getPositionProvider());
}

void World::handleEvent(const sf::Event& event)
{
    inputs->handleEvent(event);
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

