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

        b2Body* missile = physics->createBody((physics->getPosition(0).x+50)/100,
                                              physics->getPosition(0).y/100,
                                              body["width"].asFloat(),
                                              body["height"].asFloat(),
                                              body["rotation"].asFloat(),
                                              body["isDynamic"].asBool()
                                              );

        missile->SetBullet(body["isBullet"].asBool());
        missile->SetGravityScale(body["gravityScale"].asFloat());
        missile->SetLinearVelocity(b2Vec2({body["vx"].asFloat(), body["vy"].asFloat()}));

        physics->insertPosition(entity, missile->GetPosition());
        physics->insertBody(entity, missile);
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
