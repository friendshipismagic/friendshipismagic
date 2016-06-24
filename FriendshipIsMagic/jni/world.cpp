#include "world.h"
#include "physicsystem.h"
#include <string.h>
#include "filestream.hpp"

World::World(State::Context context)
: mContext(context)
, mSystems()
{
    inputs = new InputSystem(this, context);
    mSystems.push_back(inputs);

    logics = new LogicSystem(this, context, inputs);
    mSystems.push_back(logics);

    physics =  new PhysicSystem(this, context, logics);
    mSystems.push_back(physics);

    graphics = new GraphicSystem(this, context, physics);
    mSystems.push_back(graphics);

    timers = new TimerSystem(this, context);
    mSystems.push_back(timers);

    weapons = new WeaponSystem(this, context);
    mSystems.push_back(weapons);

    health = new HealthSystem(this, context, graphics);
    mSystems.push_back(health);

    graphics->setPositionProvider(physics->getPositionProvider());

    createPlayer();
    createCoPlayer();

    createEntity(Systems::Mask::WEAPONITEM, "Entities/uziitem.txt", 6, 4);
    createEntity(Systems::Mask::BLOC, "Entities/bloc1.txt", 3, 6.5);
    createEntity(Systems::Mask::BLOC, "Entities/bloc2.txt", 3, 5.2);
    createEntity(Systems::Mask::BLOC, "Entities/bloc3.txt", 6, 5.2);
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

    for(Entity entity : mEntitiesToDestroy)
    {
        destroyEntity(entity);
    }

    mEntitiesToDestroy.clear();
}

void World::draw()
{
    graphics->draw();
}

Entity World::createEntity(Systems::Mask mask, std::string fileName, float x, float y)
{
    Entity entity = mMasks.size(); //This id is not own by anyone, so we can provide it for the new Entity
    for(auto m: mMasks)
    {
        if (m.second == Systems::Mask::NONE) //We seek for an empty entity
        {
            entity = m.first;
            mMasks.erase(entity);
            break;
        }
    }
    insertMask(entity, mask); //We add the entity's mask in the map
    int scale = physics->getScale();

    //We open the JSON file
    FileStream file;
    if(!file.open(fileName))
    {
        std::cerr << "Error: can't open file " << fileName << std::endl;
        return -1;
    }

    Json::Value root;
    Json::Reader reader;
    if( !reader.parse(file.readAll(), root, false) )
    {
        std::cout << "Error while reading " + fileName + "file:\n" << reader.getFormattedErrorMessages();
        file.close();
        return -1;
    }
    else file.close();

    Json::Value components = root["components"];

    if ((mask & Systems::Component::BODY) == Systems::Component::BODY)
    {
        Json::Value body = components["body"];

        b2Body* newBody = physics->createBody(entity,
                                              x,
                                              y,
                                              body["width"].asFloat(),
                                              body["height"].asFloat(),
                                              body["rotation"].asFloat(),
                                              body["isDynamic"].asBool()
                                              );

        newBody->SetBullet(body["isBullet"].asBool());
        newBody->SetGravityScale(body["gravityScale"].asFloat());
        newBody->SetLinearVelocity(b2Vec2({body["vx"].asFloat(), body["vy"].asFloat()}));

        //physics->insertPosition(entity, newBody->GetPosition());
        physics->insertBody(entity, newBody);
    }
    if ((mask & Systems::Component::SENSOR) == Systems::Component::SENSOR)
    {
        physics->addSensor(entity, entity + 1);
        mMasks.insert(std::make_pair(entity + 1, Systems::Mask::TAKEN));
    }
    if ((mask & Systems::Component::TIMER) == Systems::Component::TIMER)
    {
        Json::Value timer = components["timer"];
        timers->insertTimer(entity, timer["time"].asFloat());
    }
    if ((mask & Systems::Component::POSITION) == Systems::Component::POSITION)
    {
        physics->insertPosition(entity, b2Vec2({scale*x, scale*y}));
    }
    if ((mask & Systems::Component::SPRITE) == Systems::Component::SPRITE)
    {
        Json::Value sprite = components["sprite"];
        graphics->insertSprite(entity, sprite["texture"].asString(), sprite["rotation"].asFloat(), sprite["width"].asFloat(), sprite["height"].asFloat());
    }
    if ((mask & Systems::Component::WEAPONTYPE) == Systems::Component::WEAPONTYPE)
    {
        std::string weaponType = components["weaponType"].asString();
        weapons->insertWeaponType(entity, weaponType);
    }
    if ((mask & Systems::Component::DAMAGE) == Systems::Component::DAMAGE)
    {
        int damage = components["damage"].asInt();
        weapons->insertDamage(entity, damage);
    }
    if ((mask & Systems::Component::HEALTH) == Systems::Component::HEALTH)
    {
        int life = components["health"].asInt();
        health->insertHealth(entity, life);

        Entity healthBarID = createEntity(Systems::Mask::GRAPHICELEMENT, "Entities/healthbar.txt", 0, -0.5);
        graphics->attachSprite(entity, healthBarID);
        health->insertHealthBar(entity, healthBarID);

        insertDependency(entity, healthBarID);
    }

    return entity;
}


void World::destroyEntity(Entity entity)
{
    std::cout << "destruction " << entity << std::endl;
    Systems::Mask mask = mMasks[entity];

    if ((mask & Systems::Component::BODY) == Systems::Component::BODY)
    {
        physics->deleteBody(entity);
    }
    if ((mask & Systems::Component::POSITION) == Systems::Component::POSITION)
    {
        physics->deletePosition(entity);
    }
    if ((mask & Systems::Component::SPRITE) == Systems::Component::SPRITE)
    {
        graphics->deleteSprite(entity);
    }
    if ((mask & Systems::Component::TIMER) == Systems::Component::TIMER)
    {
        timers->deleteTimer(entity);
    }
    if ((mask & Systems::Component::WEAPONTYPE) == Systems::Component::WEAPONTYPE)
    {
        weapons->deleteWeaponType(entity);
    }
    if ((mask & Systems::Component::DAMAGE) == Systems::Component::DAMAGE)
    {
        weapons->deleteDamage(entity);
    }
    if ((mask & Systems::Component::HEALTH) == Systems::Component::HEALTH)
    {
        health->deleteHealth(entity);
    }

    mMasks[entity] = Systems::Mask::NONE;
}

Systems::Mask World::getMask(Entity entity)
{
    return mMasks[entity];
}

void World::sigDestroyEntity(Entity entity)
{
    mEntitiesToDestroy.push_back(entity);
    if (mDependencies.find(entity) != mDependencies.end())
    {
        for (Entity entitySon : mDependencies[entity])
        {
            sigDestroyEntity(entitySon);
        }
    }
    if(entity == mPlayerID)
        createPlayer();
    if(entity == mCoPlayerID)
        createCoPlayer();
}

void World::sigTimerCall(Entity entity)
{
    Systems::Mask mask = mMasks[entity];

    if(mask == Systems::Mask::BULLET)
        mEntitiesToDestroy.push_back(entity);
    else if(mask == Systems::Mask::WEAPON)
    {
        logics->setLogic(Logic::canFire, true);
    }
    else if(mask == Systems::Mask::WEAPONITEM)
    {
        mEntitiesToDestroy.push_back(entity);
    }
}

void World::sigCollisionWeaponItem(Entity entityPlayer, Entity entityItem)
{
    mEntitiesToDestroy.push_back(entityItem);
    mEntitiesToDestroy.push_back(mPlayerWeaponID);
    mPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/" + weapons->getWeaponType(entityItem) + ".txt", 0.1, 0);
    graphics->attachSprite(mPlayerID, mPlayerWeaponID);
    insertDependency(mPlayerID,mPlayerWeaponID);
}

void World::sigCollisionBullet(Entity entityBullet, Entity entityVictim)
{
    mEntitiesToDestroy.push_back(entityBullet);
    if ((mMasks[entityVictim] & Systems::Component::HEALTH) == Systems::Component::HEALTH)
    {
        int damage = weapons->getDamage(entityBullet);
        health->addToHealth(entityVictim, damage);
    }
}

void World::timerOn(Entity entity)
{
    timers->timerOn(entity);
}

void World::insertDependency(Entity entityFather, Entity entitySon)
{
    if (mDependencies.find(entityFather) == mDependencies.end())
    {
        std::set<Entity> sons;
        sons.insert(entitySon);
        mDependencies.insert(std::make_pair(entityFather, sons));
    }
    mDependencies[entityFather].insert(entitySon);
}

void World::deleteDependency(Entity entityFather, Entity entitySon)
{
    mDependencies[entityFather].erase(entitySon);
}

void World::createPlayer()
{
    mPlayerID = createEntity(Systems::Mask::PLAYER, "Entities/player.txt", 1, 1);
    mPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/gun.txt", 0.1, 0);
    graphics->attachSprite(mPlayerID, mPlayerWeaponID);
    insertDependency(mPlayerID, mPlayerWeaponID);
    sensorOne = mPlayerID + 1;
}

void World::createCoPlayer()
{
    mCoPlayerID = createEntity(Systems::Mask::PLAYER, "Entities/player.txt", 5, 1);
    mCoPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/gun.txt", 0.1, 0);
    graphics->attachSprite(mCoPlayerID, mCoPlayerWeaponID);
    insertDependency(mCoPlayerID, mCoPlayerWeaponID);
    sensorTwo = mCoPlayerID + 1;
}

void World::insertMask(Entity entity, Systems::Mask mask)
{
    if (mMasks.find(entity) != mMasks.end())
        mMasks[entity] = mask;
    else
        mMasks.insert(std::make_pair(entity, mask));
}
