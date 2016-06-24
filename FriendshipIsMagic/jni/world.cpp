#include "world.h"
#include "physicsystem.h"
#include <string.h>

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

    mPlayerID = createEntity(Systems::Mask::PLAYER, "Entities/player.txt", 1, 1);
    mPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/gun.txt", 0, 0);
    sensorOne = mPlayerID + 1;

    mCoPlayerID = createEntity(Systems::Mask::PLAYER, "Entities/player.txt", 5, 1);
    mCoPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/gun.txt", 3, 0);
    insertDependency(mCoPlayerID,mCoPlayerWeaponID);
    sensorTwo = mCoPlayerID + 1;

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

int World::createEntity(Systems::Mask mask, std::string fileName, float x, float y)
{
    int entity = mMasks.size(); //This id is not own by anyone, so we can provide it for the new Entity
    mMasks.push_back(mask); //We add the entity's mask in the vector
    int scale = physics->getScale();

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
        mMasks.push_back(Systems::Mask::TAKEN);
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

        int healthBarID = createEntity(Systems::Mask::GRAPHICELEMENT, "Entities/healthbar.txt", 0, -0.5);
        graphics->attachSprite(entity, healthBarID);
        health->insertHealthBar(entity, healthBarID);

        insertDependency(entity, healthBarID);
    }

    return entity;
}


void World::destroyEntity(int entity)
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

Systems::Mask World::getMask(int entity)
{
    return mMasks[entity];
}

void World::sigDestroyEntity(int entity)
{
    mEntitiesToDestroy.push_back(entity);
    if (mDependencies.find(entity) != mDependencies.end())
    {
        for (int entitySon : mDependencies[entity])
        {
            sigDestroyEntity(entitySon);
        }
    }
}

void World::sigTimerCall(int entity)
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

void World::sigCollisionWeaponItem(int entityPlayer, int entityItem)
{
    mEntitiesToDestroy.push_back(entityItem);
    mEntitiesToDestroy.push_back(mPlayerWeaponID);
    mPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/" + weapons->getWeaponType(entityItem) + ".txt", 0, 0);
}

void World::sigCollisionBullet(int entityBullet, int entityVictim)
{
    mEntitiesToDestroy.push_back(entityBullet);
    if ((mMasks[entityVictim] & Systems::Component::HEALTH) == Systems::Component::HEALTH)
    {
        int damage = weapons->getDamage(entityBullet);
        health->addToHealth(entityVictim, damage);
    }
}

void World::timerOn(int entity)
{
    timers->timerOn(entity);
}

void World::insertDependency(int entityFather, int entitySon)
{
    if (mDependencies.find(entityFather) == mDependencies.end())
    {
        std::set<int> sons;
        sons.insert(entitySon);
        mDependencies.insert(std::make_pair(entityFather, sons));
    }
    mDependencies[entityFather].insert(entitySon);
}

void World::deleteDependency(int entityFather, int entitySon)
{
    mDependencies[entityFather].erase(entitySon);
}
