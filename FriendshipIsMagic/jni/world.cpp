#include "world.h"
#include "physicsystem.h"
#include <string.h>

World::World(State::Context context)
: mSystems()
{
    inputs = new InputSystem(this, context);
    mSystems.push_back(inputs);

    physics =  new PhysicSystem(this, context, inputs);
    mSystems.push_back(physics);

    graphics = new GraphicSystem(this, context, physics);
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

void World::createEntity(Systems::Mask mask, std::string fileName)
{
    int entity = mMasks.size(); //This id is not own by anyone, so we can provide it for the new Entity
    mMasks.push_back(mask); //We add the entity's mask in the vector

    if ((mask & Systems::Component::BODY) == Systems::Component::BODY)
    {
        b2Body* missile = physics->createBody((physics->getPosition(0).x+50)/100, physics->getPosition(0).y/100, 0.1f, 0.1f, 0, true);
        missile->SetBullet(true);
        missile->SetGravityScale(0);

        physics->insertPosition(entity, missile->GetPosition());
        physics->insertBody(entity, missile);

        missile->SetLinearVelocity(b2Vec2({5.f, 0.f}));
    }
    if ((mask & Systems::Component::POSITION) == Systems::Component::POSITION)
    {

    }
    if ((mask & Systems::Component::SPRITE) == Systems::Component::SPRITE)
    {
        graphics->insertSprite(entity, "Bullet", 0, 20, 20);
    }

}
