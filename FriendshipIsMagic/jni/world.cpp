#include "World.hpp"
#include "PhysicSystem.h"
#include <string.h>

World::World(State::Context context)
: cpt(0)
, mSystems()
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

    if (physics->fire)
        createEntity(Systems::GRAPHIC, "re");
}

void World::draw()
{
    graphics->draw();
}

void World::createEntity(Systems::Mask mask, std::string fileName)
{
    int entity = cpt + 4;
    graphics->insertSprite(entity, "Skull", 0, 20, 20);

    b2Body* missile = physics->createBody((physics->getPosition(0).x+50)/100, physics->getPosition(0).y/100, 0.1f, 0.1f, 0, true);
    missile->SetBullet(true);
    missile->SetGravityScale(0);

    physics->insertPosition(entity, missile->GetPosition());
    physics->insertBody(entity, missile);

    missile->SetLinearVelocity(b2Vec2({5.f, 0.f}));

    cpt++;
}
