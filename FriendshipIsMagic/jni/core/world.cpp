#include "world.h"
#include <string.h>
#include "../ressources/filestream.hpp"
#include "player.h"


World::World(State::Context& context)
: mContext(context)
, mSystems()
, mInputs(this, context)
, mNetwork(this, context, &mInputs, &mPhysics, &mHealth, &mLogics, &mWeapons)
, mLogics(this, context,  &mInputs, &mNetwork)
, mPhysics(this,context, &mLogics)
, mGraphics(this, context, &mPhysics, &mLogics)
, mTimers(this, context )
, mWeapons(this, context)
, mHealth(this, context, &mGraphics)
, mItems(this, context)
, mScores(this, context)
, mSounds(this, context)
, mAi(this, context)
{

    mSystems.push_back(&mInputs);
    mSystems.push_back(&mNetwork);
    mSystems.push_back(&mLogics);
    mSystems.push_back(&mPhysics);
    mSystems.push_back(&mGraphics);
    mSystems.push_back(&mTimers);
    mSystems.push_back(&mWeapons);
    mSystems.push_back(&mHealth);
    mSystems.push_back(&mItems);
    mSystems.push_back(&mScores);
    mSystems.push_back(&mSounds);
    mSystems.push_back(&mAi);

    mGraphics.setPositionProvider(mPhysics.getPositionProvider());

}
/*
//=====================[ INIT SYNC METHODS ]======================//
void World::askForInit(){
	if(mContext.UDPMode == UDPAgent::Mode::Client)
	mNetwork.askForInit();
}

bool World::initEntitiesFromServer(){
	return false;
}
*/
//===================[ END INIT SYNC METHODS ]====================//


void World::sendReady(){
	mNetwork.sendReady();
}

void World::initEntities(){
	createPlayer();
	createCoPlayer();

	createEntity(Systems::Mask::ITEM, "Entities/uziitem.txt", 6, 4);
	createEntity(Systems::Mask::ITEM, "Entities/swapitem.txt", 7, 5);
	createEntity(Systems::Mask::ITEM, "Entities/raygunitem.txt", 8, 5);
	createEntity(Systems::Mask::ITEM, "Entities/shotgunitem.txt", 1, 5);
	createEntity(Systems::Mask::ITEM, "Entities/healitem.txt", 3, 5.5);
	createEntity(Systems::Mask::ITEM, "Entities/increasemaxlifeitem.txt", 4, 5.5);
	createEntity(Systems::Mask::BLOC, "Entities/bloc1.txt", 3, 6.5);
	createEntity(Systems::Mask::BLOC, "Entities/bloc2.txt", 9, 5.2);
	createEntity(Systems::Mask::BLOC, "Entities/bloc3.txt", 6, 5.2);
	createEntity(Systems::Mask::MONSTER, "Entities/monster.txt", 10, 4);

    mAi.setMatrix("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEWWWWWWWWWWWWWWWW",16);
}
//Server mode
void World::startUDPServer(int srcPort){
	mNetwork.startUDPServer(srcPort);
}
//Client mode
void World::startUDPClient(int srcPort, sf::IpAddress destIp, int destPort){
	mNetwork.startUDPClient(srcPort, destIp, destPort);
}
void World::handleEvent(const sf::Event& event)
{
    mInputs.handleEvent(event);
}

void World::update(sf::Time dt)
{
	if(mNetwork.isInitialized()){
    for(auto itr = mSystems.rbegin(); itr != mSystems.rend(); ++itr)
    {
        (*itr)->update(dt);
    }

    for(Entity entity : mEntitiesToDestroy)
    {
        destroyEntity(entity);
    }

    mEntitiesToDestroy.clear();

    bool playerDead = mMasks[mPlayerID] == Systems::Mask::NONE;
    bool coPlayerDead = mMasks[mCoPlayerID] == Systems::Mask::NONE;
    if(playerDead)
    {
        createPlayer();
        mScores.addToScore(mPlayerID, -1000);
    }
    if(coPlayerDead)
    {
        createCoPlayer();
        mScores.addToScore(mCoPlayerID, -1000);
    }

    if (mLogics.getLogic(Logic::fireOn) && mLogics.getLogic(Logic::canFire))
    {
        sf::Vector2f pos = mPhysics.getPosition(mPlayerID);
        int scale = mPhysics.getScale();
        std::string weaponType = mWeapons.getWeaponType(mPlayerWeaponID);
        if(mLogics.getLogic(Logic::isFacingLeft))
        {
            int bullet = createEntity(Systems::BULLET, "Entities/bullet" + weaponType + ".txt", pos.x/scale, pos.y/scale);
            mWeapons.insertOwner(bullet, mPlayerID);
        }
        else
        {
            paddingRight = true;
            int bullet = createEntity(Systems::BULLET, "Entities/bullet" + weaponType + ".txt", pos.x/scale, pos.y/scale);
            paddingRight = false;
            mWeapons.insertOwner(bullet, mPlayerID);
            mGraphics.mirror(bullet, -1);
            mPhysics.mirrorVelocity(bullet);
        }

        mLogics.setLogic(Logic::canFire, false);
        timerOn(mPlayerWeaponID);

        mSounds.play(weaponType);
    }

    if (mLogics.getLogic(Logic::coFireOn) && mLogics.getLogic(Logic::coCanFire))
    {
        sf::Vector2f pos = mPhysics.getPosition(mCoPlayerID);
        int scale = mPhysics.getScale();
        std::string weaponType = mWeapons.getWeaponType(mCoPlayerWeaponID);

        if(mLogics.getLogic(Logic::coIsFacingLeft))
        {
            int bullet = createEntity(Systems::BULLET, "Entities/bullet" + weaponType + ".txt", pos.x/scale, pos.y/scale);
            mWeapons.insertOwner(bullet, mCoPlayerID);
        }
        else
        {
            paddingRight = true;
            int bullet = createEntity(Systems::BULLET, "Entities/bullet" + weaponType + ".txt", pos.x/scale, pos.y/scale);
            paddingRight = false;
            mWeapons.insertOwner(bullet, mCoPlayerID);
            mGraphics.mirror(bullet, -1);
            mPhysics.mirrorVelocity(bullet);
        }

        mLogics.setLogic(Logic::coCanFire, false);
        timerOn(mCoPlayerWeaponID);

        mSounds.play(weaponType);
    }
	}
	else
		mNetwork.update( dt);

}

void World::draw()
{
    mGraphics.draw();
}

Entity World::createEntity(Systems::Mask mask, std::string fileName, float x, float y)
{
    Entity entity = mMasks.size(); //This id is not own by anyone, so we can provide it for the new Entity
    for(auto m: mMasks)
    {
        if ((m.second == Systems::Mask::NONE) && (m.first != mPlayerID) && (m.first != mCoPlayerID)) //We seek for an empty entity
        {
            entity = m.first;
            mMasks.erase(entity);
            break;
        }
    }
    insertMask(entity, mask); //We add the entity's mask in the map

    int scale = mPhysics.getScale();


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

    if ((mask & Systems::Component::PADDING) == Systems::Component::PADDING)
    {
        Json::Value padding = components["padding"];
        if (paddingRight)
            x += padding["x"].asFloat();
        else
            x -= padding["x"].asFloat();
        y += padding["y"].asFloat();
    }
    if ((mask & Systems::Component::BODY) == Systems::Component::BODY)
    {
        Json::Value body = components["body"];

        b2Body* newBody = mPhysics.createBody(entity,
                                              x,
                                              y,
                                              body["width"].asFloat(),
                                              body["height"].asFloat(),
                                              body["rotation"].asFloat(),
                                              body["isDynamic"].asBool(),
                                              body["isSensor"].asBool()
                                              );

        newBody->SetBullet(body["isBullet"].asBool());
        newBody->SetGravityScale(body["gravityScale"].asFloat());
        newBody->SetLinearVelocity(b2Vec2({body["vx"].asFloat(), body["vy"].asFloat()}));

        mPhysics.insertBody(entity, newBody);
    }
    if ((mask & Systems::Component::SENSOR) == Systems::Component::SENSOR)
    {
        Json::Value sensor = components["sensor"];
        Entity owner = mPlayerID;
        if(!sensor["isPlayerSensor"].asBool())
            owner = mCoPlayerID;

        mPhysics.addSensor(entity,
                          owner,
                          sensor["x"].asFloat(),
                          sensor["y"].asFloat(),
                          sensor["width"].asFloat(),
                          sensor["height"].asFloat()
                          );
    }
    if ((mask & Systems::Component::NETWORKID) == Systems::Component::NETWORKID)
	{
    	if(mContext.UDPMode != UDPAgent::None)
    		mNetwork.insertNetworkID(entity);
	}
    if ((mask & Systems::Component::TIMER) == Systems::Component::TIMER)
    {
        Json::Value timer = components["timer"];
        mTimers.insertTimer(entity, timer["time"].asFloat());
    }
    if ((mask & Systems::Component::POSITION) == Systems::Component::POSITION)
    {
        mPhysics.insertPosition(entity, b2Vec2({scale*x, scale*y}));
    }
    if ((mask & Systems::Component::SPRITE) == Systems::Component::SPRITE)
    {
        Json::Value sprite = components["sprite"];
        mGraphics.insertSprite(entity, sprite["texture"].asString(), sprite["rotation"].asFloat(), sprite["width"].asFloat(), sprite["height"].asFloat());
    }
    if ((mask & Systems::Component::ITEMTYPE) == Systems::Component::ITEMTYPE)
    {
        ItemType type = mItems.fromString(components["type"].asString());
        mItems.insertType(entity, type);
        if (type == ItemType::weapon)
            mWeapons.insertWeaponType(entity, components["weaponType"].asString());
    }
    if ((mask & Systems::Component::WEAPONTYPE) == Systems::Component::WEAPONTYPE)
    {
        mWeapons.insertWeaponType(entity, components["weaponType"].asString());
    }
    if ((mask & Systems::Component::DAMAGE) == Systems::Component::DAMAGE)
    {
        int damage = components["damage"].asInt();
        mWeapons.insertDamage(entity, damage);
    }
    if ((mask & Systems::Component::HEALTH) == Systems::Component::HEALTH)
    {
        int life = components["health"].asInt();
        mHealth.insertHealth(entity, life);

        Entity healthBarID = createEntity(Systems::Mask::HEALTHBAR, "Entities/healthbar.txt", 0, 0);
        mGraphics.insertDependency(entity, healthBarID);
        mHealth.insertHealthBar(entity, healthBarID);

        insertDependency(entity, healthBarID);
    }
    if ((mask & Systems::Component::SCORE) == Systems::Component::SCORE)
    {
        mScores.insertScore(entity, 0);
    }

    return entity;
}


void World::destroyEntity(Entity entity)
{
    std::cout << "destruction " << entity << " " << mMasks[entity] << std::endl;
    Systems::Mask mask = mMasks[entity];

    if ((mask & Systems::Component::BODY) == Systems::Component::BODY)
    {

        mPhysics.deleteBody(entity);
    }
    if ((mask & Systems::Component::POSITION) == Systems::Component::POSITION)
    {
        mPhysics.deletePosition(entity);
    }
    if ((mask & Systems::Component::SPRITE) == Systems::Component::SPRITE)
    {
        mGraphics.deleteSprite(entity);
    }
    if ((mask & Systems::Component::TIMER) == Systems::Component::TIMER)
    {
        mTimers.deleteTimer(entity);
    }
    if ((mask & Systems::Component::ITEMTYPE) == Systems::Component::ITEMTYPE)
    {
        if (mItems.getType(entity) == ItemType::weapon)
            mWeapons.deleteWeaponType(entity);

        mItems.deleteType(entity);
    }
    if ((mask & Systems::Component::DAMAGE) == Systems::Component::DAMAGE)
    {
        mWeapons.deleteDamage(entity);
    }
    if ((mask & Systems::Component::HEALTH) == Systems::Component::HEALTH)
    {
        mHealth.deleteHealth(entity);
    }
    if ((mask & Systems::Component::OWNER) == Systems::Component::OWNER)
    {
        mWeapons.deleteOwner(entity);
    }

    mMasks[entity] = Systems::Mask::NONE;

    if (mSons.find(entity) != mSons.end())
    {
        mSons.erase(entity);
    }
}

Systems::Mask World::getMask(Entity entity)
{
    return mMasks[entity];
}

void World::sigDestroyEntity(Entity entity)
{
    if(mEntitiesToDestroy.find(entity) == mEntitiesToDestroy.end())
    {
        std::cout << "Entity " << entity << " " << mMasks[entity] << std::endl;
        mEntitiesToDestroy.insert(entity);
        if (mSons.find(entity) != mSons.end())
        {
            for (auto itr = mSons[entity].begin(); itr != mSons[entity].end() ; itr++)
            {
                sigDestroyEntity(*itr);
            }
        }
    }
}

void World::sigTimerCall(Entity entity)
{
    Systems::Mask mask = mMasks[entity];

    if(mask == Systems::Mask::BULLET)
        sigDestroyEntity(entity);
    else if(entity == mPlayerWeaponID)
    {
        mLogics.setLogic(Logic::canFire, true);
    }
    else if(entity == mCoPlayerWeaponID)
    {
        mLogics.setLogic(Logic::coCanFire, true);
    }
    else if(mask == Systems::Mask::ITEM)
    {
        sigDestroyEntity(entity);
    }
}

void World::sigCollisionItem(Entity entityPlayer, Entity entityItem)
{
    sigDestroyEntity(entityItem);
    ItemType type = mItems.getType(entityItem);

    if (type == ItemType::weapon)
    {
        Entity weapon = mPlayerWeaponID;
        if (entityPlayer == mCoPlayerID)
            weapon = mCoPlayerWeaponID;

        sigDestroyEntity(weapon);
        std::string weaponType = mWeapons.getWeaponType(entityItem);
        weapon = createEntity(Systems::Mask::WEAPON, "Entities/" + weaponType + ".txt", 0, 0);
        mGraphics.insertDependency(entityPlayer, weapon);
        insertDependency(entityPlayer, weapon);
        mWeapons.insertWeaponType(entityPlayer, weaponType);

        if (entityPlayer == mCoPlayerID)
            mCoPlayerWeaponID = weapon;
        else
            mPlayerWeaponID = weapon;

        if(mLogics.getLogic(Logic::coIsFacingRight) && (weapon == mCoPlayerWeaponID) )
            mGraphics.mirror(weapon, -1);
        else if(mLogics.getLogic(Logic::isFacingRight) && (weapon == mPlayerWeaponID) )
            mGraphics.mirror(weapon, -1);
    }
    else if (type == ItemType::swapstuff)
    {
        std::string coweapon = mWeapons.getWeaponType(mCoPlayerWeaponID);
        std::string weapon = mWeapons.getWeaponType(mPlayerWeaponID);

        sigDestroyEntity(mPlayerWeaponID);
        deleteDependency(mPlayerID, mPlayerWeaponID);
        mPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/" + coweapon + ".txt", 0, 0);
        mGraphics.insertDependency(mPlayerID, mPlayerWeaponID);
        insertDependency(mPlayerID, mPlayerWeaponID);

        sigDestroyEntity(mCoPlayerWeaponID);
        deleteDependency(mCoPlayerID, mCoPlayerWeaponID);
        mCoPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/" + weapon + ".txt", 0, 0);
        mGraphics.insertDependency(mCoPlayerID, mCoPlayerWeaponID);
        insertDependency(mCoPlayerID, mCoPlayerWeaponID);

        mWeapons.insertWeaponType(mPlayerWeaponID, coweapon);
        mWeapons.insertWeaponType(mCoPlayerWeaponID, weapon);

        if(mLogics.getLogic(Logic::coIsFacingRight))
            mGraphics.mirror(mCoPlayerWeaponID, -1);
        else if(mLogics.getLogic(Logic::isFacingRight))
            mGraphics.mirror(mPlayerWeaponID, -1);
    }
    else if (type == ItemType::heal)
        mHealth.addToHealth(entityPlayer, +50);
    else if (type == ItemType::increaseMaxLife)
        mHealth.insertHealth(entityPlayer, mHealth.getMaxHealth(entityPlayer) + 50 );
}

void World::sigCollisionBullet(Entity entityBullet, Entity entityVictim)
{
    Entity owner = mWeapons.getOwner(entityBullet);
    std::string weaponType = mWeapons.getWeaponType(mPlayerWeaponID);
    if (owner == mCoPlayerID)
        weaponType = mWeapons.getWeaponType(mCoPlayerWeaponID);
    if(entityVictim != owner)
    {
        if((weaponType.compare("shotgun")) != 0 && (weaponType.compare("raygun") != 0) && (mMasks[entityVictim] != Systems::Mask::ITEM))
            sigDestroyEntity(entityBullet);
        if ((mMasks[entityVictim] & Systems::Component::HEALTH) == Systems::Component::HEALTH)
        {
            Entity weapon = mPlayerWeaponID;
            if (owner == mCoPlayerID)
                weapon = mCoPlayerWeaponID;

            int damage = mWeapons.getDamage(weapon);
            mHealth.addToHealth(entityVictim, damage);
        }

        if ((entityVictim == mPlayerID) || (entityVictim == mCoPlayerID))
        {
            mSounds.play("Hit");
        }
    }
}

void World::timerOn(Entity entity)
{
    mTimers.timerOn(entity);
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
        if (mSons[entityFather].find(entitySon) != mSons[entityFather].end())
            mSons[entityFather].erase(entitySon);

    if (mFathers.find(entitySon) != mFathers.end())
    {
        mFathers.erase(entitySon);
    }
}

void World::createPlayer()
{
    mPlayerID = createEntity(Systems::Mask::PLAYER, "Entities/player.txt", Player::SpawnLocationX, Player::SpawnLocationY);
    mPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/gun.txt", 0, 0);
    mGraphics.insertDependency(mPlayerID, mPlayerWeaponID);
    insertDependency(mPlayerID, mPlayerWeaponID);
    sensorOne = createEntity(Systems::Mask::FOOTSENSOR, "Entities/playerfootsensor.txt", 0, 0);
    insertDependency(mPlayerID, sensorOne);
}

void World::createCoPlayer()
{
    mCoPlayerID = createEntity(Systems::Mask::PLAYER, "Entities/coplayer.txt", Player::SpawnLocationX, Player::SpawnLocationY);
    mCoPlayerWeaponID = createEntity(Systems::Mask::WEAPON, "Entities/gun.txt", 0, 0);
    mGraphics.insertDependency(mCoPlayerID, mCoPlayerWeaponID);
    insertDependency(mCoPlayerID, mCoPlayerWeaponID);
    sensorTwo = createEntity(Systems::Mask::FOOTSENSOR, "Entities/coplayerfootsensor.txt", 0, 0);
    insertDependency(mCoPlayerID, sensorTwo);
}

void World::insertMask(Entity entity, Systems::Mask mask)
{
    if (mMasks.find(entity) != mMasks.end())
        mMasks[entity] = mask;
    else
        mMasks.insert(std::make_pair(entity, mask));
}

