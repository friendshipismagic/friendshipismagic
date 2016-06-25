#include "world.h"
#include "physicsystem.h"
#include <string.h>
#include "filestream.hpp"
#include "player.h"

World::World(State::Context context)
: mContext(context)
, mSystems()
{
    mInputs = new InputSystem(this, context);
    mSystems.push_back(mInputs);

    mLogics = new LogicSystem(this, context, mInputs);
    mSystems.push_back(mLogics);

    mPhysics =  new PhysicSystem(this, context, mLogics);
    mSystems.push_back(mPhysics);

    mGraphics = new GraphicSystem(this, context, mPhysics, mLogics);
    mSystems.push_back(mGraphics);

    mTimers = new TimerSystem(this, context);
    mSystems.push_back(mTimers);

    mWeapons = new WeaponSystem(this, context);
    mSystems.push_back(mWeapons);

    mHealth = new HealthSystem(this, context, mGraphics);
    mSystems.push_back(mHealth);

    mItems = new ItemSystem(this, context);
    mSystems.push_back(mItems);

    mGraphics->setPositionProvider(mPhysics->getPositionProvider());

    createPlayer();
    createCoPlayer();

    createEntity(Systems::Mask::ITEM, "Entities/uziitem.txt", 6, 4);
    createEntity(Systems::Mask::ITEM, "Entities/swapitem.txt", 7, 5);
    createEntity(Systems::Mask::BLOC, "Entities/bloc1.txt", 3, 6.5);
    createEntity(Systems::Mask::BLOC, "Entities/bloc2.txt", 3, 5.2);
    createEntity(Systems::Mask::BLOC, "Entities/bloc3.txt", 6, 5.2);
}

void World::handleEvent(const sf::Event& event)
{
    mInputs->handleEvent(event);
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

    if(mMasks[mPlayerID] == Systems::Mask::NONE)
        createPlayer();
    if(mMasks[mCoPlayerID] == Systems::Mask::NONE)
        createCoPlayer();
}

void World::draw()
{
    mGraphics->draw();
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
    int scale = mPhysics->getScale();

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

        b2Body* newBody = mPhysics->createBody(entity,
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

        mPhysics->insertBody(entity, newBody);
    }
    if ((mask & Systems::Component::SENSOR) == Systems::Component::SENSOR)
    {
        mPhysics->addSensor(entity, entity + 1);
        mMasks.insert(std::make_pair(entity + 1, Systems::Mask::TAKEN));
    }
    if ((mask & Systems::Component::TIMER) == Systems::Component::TIMER)
    {
        Json::Value timer = components["timer"];
        mTimers->insertTimer(entity, timer["time"].asFloat());
    }
    if ((mask & Systems::Component::POSITION) == Systems::Component::POSITION)
    {
        mPhysics->insertPosition(entity, b2Vec2({scale*x, scale*y}));
    }
    if ((mask & Systems::Component::SPRITE) == Systems::Component::SPRITE)
    {
        Json::Value sprite = components["sprite"];
        mGraphics->insertSprite(entity, sprite["texture"].asString(), sprite["rotation"].asFloat(), sprite["width"].asFloat(), sprite["height"].asFloat());
    }
    if ((mask & Systems::Component::ITEMTYPE) == Systems::Component::ITEMTYPE)
    {
        ItemType type = mItems->fromString(components["type"].asString());
        mItems->insertType(entity, type);
        if (type == ItemType::weapon)
            mWeapons->insertWeaponType(entity, components["weaponType"].asString());
    }
    if ((mask & Systems::Component::WEAPONTYPE) == Systems::Component::WEAPONTYPE)
    {
        mWeapons->insertWeaponType(entity, components["weaponType"].asString());
    }
    if ((mask & Systems::Component::DAMAGE) == Systems::Component::DAMAGE)
    {
        int damage = components["damage"].asInt();
        mWeapons->insertDamage(entity, damage);
    }
    if ((mask & Systems::Component::HEALTH) == Systems::Component::HEALTH)
    {
        int life = components["health"].asInt();
        mHealth->insertHealth(entity, life);

        Entity healthBarID = createEntity(Systems::Mask::GRAPHICELEMENT, "Entities/healthbar.txt", 0, Player::HealthBarTopPadding);
        mGraphics->insertDependency(entity, healthBarID);
        mHealth->insertHealthBar(entity, healthBarID);

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
        mPhysics->deleteBody(entity);
    }
    if ((mask & Systems::Component::POSITION) == Systems::Component::POSITION)
    {
        mPhysics->deletePosition(entity);
    }
    if ((mask & Systems::Component::SPRITE) == Systems::Component::SPRITE)
    {
        mGraphics->deleteSprite(entity);
    }
    if ((mask & Systems::Component::TIMER) == Systems::Component::TIMER)
    {
        mTimers->deleteTimer(entity);
    }
    if ((mask & Systems::Component::ITEMTYPE) == Systems::Component::ITEMTYPE)
    {
        if (mItems->getType(entity) == ItemType::weapon)
            mWeapons->deleteWeaponType(entity);

        mItems->deleteType(entity);
    }
    if ((mask & Systems::Component::DAMAGE) == Systems::Component::DAMAGE)
    {
        mWeapons->deleteDamage(entity);
    }
    if ((mask & Systems::Component::HEALTH) == Systems::Component::HEALTH)
    {
        mHealth->deleteHealth(entity);
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
    if (mSons.find(entity) != mSons.end())
    {
        for (Entity entitySon : mSons[entity])
        {
            deleteDependency(entity, entitySon);
            sigDestroyEntity(entitySon);
        }
    }
    if (mFathers.find(entity) != mFathers.end())
    {
        deleteDependency(mFathers[entity], entity);
        mFathers.erase(entity);
    }
}

void World::sigTimerCall(Entity entity)
{
    Systems::Mask mask = mMasks[entity];

    if(mask == Systems::Mask::BULLET)
        mEntitiesToDestroy.push_back(entity);
    else if(mask == Systems::Mask::WEAPON)
    {
        mLogics->setLogic(Logic::canFire, true);
    }
    else if(mask == Systems::Mask::ITEM)
    {
        mEntitiesToDestroy.push_back(entity);
    }
}

void World::sigCollisionItem(Entity entityPlayer, Entity entityItem)
{
    mEntitiesToDestroy.push_back(entityItem);
    ItemType type = mItems->getType(entityItem);

    if (type == ItemType::weapon)
    {
        Entity weapon = mPlayerWeaponID;
        if (entityPlayer == mCoPlayerID)
            weapon = mCoPlayerWeaponID;

        mEntitiesToDestroy.push_back(weapon);
        std::string weaponType = mWeapons->getWeaponType(entityItem);
        weapon = createEntity(Systems::Mask::WEAPON, "Entities/" + weaponType + ".txt", Player::WeaponHorizontalPadding, Player::WeaponTopPadding);
        mGraphics->insertDependency(entityPlayer, weapon);
        insertDependency(entityPlayer, weapon);
        mWeapons->insertWeaponType(entityPlayer, weaponType);

        if (entityPlayer == mCoPlayerID)
             mCoPlayerWeaponID = weapon;
        else
            mPlayerWeaponID = weapon;
    }
    else if (type == ItemType::swapstuff)
    {
        std::string coweapon = mWeapons->getWeaponType(mCoPlayerID);
        std::string weapon = mWeapons->getWeaponType(mPlayerID);

        mEntitiesToDestroy.push_back(mPlayerWeaponID);
        mPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/" + coweapon + ".txt", Player::WeaponHorizontalPadding, Player::WeaponTopPadding);
        mGraphics->insertDependency(mPlayerID, mPlayerWeaponID);
        insertDependency(mPlayerID, mPlayerWeaponID);

        mEntitiesToDestroy.push_back(mCoPlayerWeaponID);
        mCoPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/" + weapon + ".txt", Player::WeaponHorizontalPadding, Player::WeaponTopPadding);
        mGraphics->insertDependency(mCoPlayerID, mCoPlayerWeaponID);
        insertDependency(mCoPlayerID, mCoPlayerWeaponID);

        mWeapons->insertWeaponType(mPlayerID, coweapon);
        mWeapons->insertWeaponType(mCoPlayerID, weapon);
    }
}

void World::sigCollisionBullet(Entity entityBullet, Entity entityVictim)
{
    mEntitiesToDestroy.push_back(entityBullet);
    if ((mMasks[entityVictim] & Systems::Component::HEALTH) == Systems::Component::HEALTH)
    {
        int damage = mWeapons->getDamage(entityBullet);
        mHealth->addToHealth(entityVictim, damage);
    }
}

void World::timerOn(Entity entity)
{
    mTimers->timerOn(entity);
}

void World::insertDependency(Entity entityFather, Entity entitySon)
{
    if (mSons.find(entityFather) == mSons.end())
    {
        std::set<Entity> sons;
        sons.insert(entitySon);
        mSons.insert(std::make_pair(entityFather, sons));
    }
    else
        mSons[entityFather].insert(entitySon);

    if (mFathers.find(entitySon) == mFathers.end())
    {
        mFathers.insert(std::make_pair(entitySon, entityFather));
    }
    else
        mFathers[entitySon] = entityFather;
}

void World::deleteDependency(Entity entityFather, Entity entitySon)
{
    if (mSons.find(entityFather) != mSons.end())
        mSons[entityFather].erase(entitySon);

    if (mFathers.find(entitySon) == mFathers.end())
    {
        mFathers.erase(entitySon);
    }
}

void World::createPlayer()
{
    mPlayerID = createEntity(Systems::Mask::PLAYER, "Entities/player.txt", Player::SpawnLocationX, Player::SpawnLocationY);
    mPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/gun.txt", Player::WeaponHorizontalPadding, Player::WeaponTopPadding);
    mGraphics->insertDependency(mPlayerID, mPlayerWeaponID);
    insertDependency(mPlayerID, mPlayerWeaponID);
    sensorOne = mPlayerID + 1;
}

void World::createCoPlayer()
{
    mCoPlayerID = createEntity(Systems::Mask::PLAYER, "Entities/player.txt", Player::SpawnLocationX, Player::SpawnLocationY);
    mCoPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/gun.txt", Player::WeaponHorizontalPadding, Player::WeaponTopPadding);
    mGraphics->insertDependency(mCoPlayerID, mCoPlayerWeaponID);
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
