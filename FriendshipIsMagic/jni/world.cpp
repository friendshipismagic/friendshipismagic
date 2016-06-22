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

    for(int entity : mEntitiesToDestroy)
    {
        destroyEntity(entity);
    }

    mEntitiesToDestroy.clear();
}

void World::draw()
{
    graphics->draw();
}

int World::createEntity(Systems::Mask mask, std::string fileName)
{
    int entity = mMasks.size(); //This id is not own by anyone, so we can provide it for the new Entity
    mMasks.push_back(mask); //We add the entity's mask in the vector

    //We open the JSON file
    std::ifstream file(fileName.c_str());
    if (!file)
    {
        std::cerr << "Error: can't open file " << fileName << std::endl;
        return -1;
    }

    Json::Value root;
    Json::Reader reader;
    if( !reader.parse(file, root, false) )
    {
        std::cout << "Error while reading " + fileName + "file:\n" << reader.getFormattedErrorMessages();
        return -1;
    }

    Json::Value components = root["components"];

    if ((mask & Systems::Component::BODY) == Systems::Component::BODY)
    {
        Json::Value body = components["body"];


        b2Body* newBody = physics->createBody(entity,
                                              body["x"].asFloat(),
                                              body["y"].asFloat(),
                                              body["width"].asFloat(),
                                              body["height"].asFloat(),
                                              body["rotation"].asFloat(),
                                              body["isDynamic"].asBool()
                                              );

        missile->SetBullet(body["isBullet"].asBool());
        missile->SetGravityScale(body["gravityScale"].asFloat());
        missile->SetLinearVelocity(b2Vec2({body["vx"].asFloat(), body["vy"].asFloat()}));

        physics->insertPosition(entity, newBody->GetPosition());
        physics->insertBody(entity, newBody);
    }
    if ((mask & Systems::Component::SENSOR) == Systems::Component::SENSOR)
    {
        Json::Value sensor = components["sensor"];
        physics->addSensor(entity, sensor["ID"].asInt());
    }
    if ((mask & Systems::Component::POSITION) == Systems::Component::POSITION)
    {

    }
    if ((mask & Systems::Component::SPRITE) == Systems::Component::SPRITE)
    {
        Json::Value sprite = components["sprite"];
        graphics->insertSprite(entity, sprite["texture"].asString(), sprite["rotation"].asFloat(), sprite["width"].asFloat(), sprite["height"].asFloat());
    }

    return entity;
}


void World::destroyEntity(int entity)
{
    std::cout << "destruction" << std::endl;
    Systems::Mask mask = mMasks[entity];

    if ((mask & Systems::Component::BODY) == Systems::Component::BODY)
    {
        physics->deletePosition(entity);
        physics->deleteBody(entity);
    }
    if ((mask & Systems::Component::POSITION) == Systems::Component::POSITION)
    {

    }
    if ((mask & Systems::Component::SPRITE) == Systems::Component::SPRITE)
    {
        graphics->deleteSprite(entity);
    }
    if ((mask & Systems::Component::TIMER) == Systems::Component::TIMER)
    {
        timers->deleteTimer(entity);
    }

    mMasks[entity] = Systems::Mask::NONE;
}

Systems::Mask World::getMask(int entity)
{
    return mMasks[entity];
}

void World::sigDestroyEntity(int entity)
{
    mEntitiesToDestroy.push_back(entity);
}
