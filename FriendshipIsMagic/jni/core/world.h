#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "../systems/systemprovider.h"
#include "../states/state.h"

#include <Box2D/Box2D.h>
#include <set>
#include "../systems/graphicsystem.h"
#include "../systems/system.h"

#include "../systems/inputsystem.h"
#include "../systems/physicsystem.h"
#include "../systems/timersystem.h"
#include "../systems/logicsystem.h"
#include "../systems/weaponsystem.h"
#include "../systems/healthsystem.h"
#include "../systems/itemsystem.h"
#include "../systems/scoresystem.h"
#include "../systems/soundsystem.h"
#include "../systems/network-system.h"
#include "../systems/aisystem.h"
#include <Box2D/Box2D.h>
#include <set>
#include "entity.h"

class World
{
    public:

        World(State::Context& context);
        void update(sf::Time dt);
        void draw();
        void handleEvent(const sf::Event& event);

        Entity createEntity(Systems::Mask mask, std::string fileName, float x, float y);

        void destroyEntity(Entity entity);
        void sigDestroyEntity(Entity entity);
        void sigTimerCall(Entity entity);
        void sigCollisionItem(Entity entityPlayer, Entity entityItem);
        void sigCollisionBullet(Entity entityBullet, Entity entityVictim);
        void timerOn(Entity entity);

        Systems::Mask getMask(Entity entity) const;

        Entity getPlayerID() const { return mPlayerID; };
        Entity getPlayerWeaponID() const { return mPlayerWeaponID; };
        void setPlayerWeaponID(Entity entity) { mPlayerWeaponID = entity; };
        Entity getPlayerSensorID() const { return sensorOne; };

        Entity getCoPlayerID() const { return mCoPlayerID; };
        Entity getCoPlayerWeaponID() const { return mCoPlayerWeaponID; };
        void setCoPlayerWeaponID(Entity entity) { mCoPlayerWeaponID = entity; };
        Entity getCoPlayerSensorID() const { return sensorTwo; };

        void insertDependency(Entity entityFather, Entity entitySon);
        void deleteDependency(Entity entityFather, Entity entitySon);

        void createPlayer();
        void createCoPlayer();
        void startUDPServer(int srcPort);
        void startUDPClient(int srcPort, sf::IpAddress destIp, int destPort);
        void initEntities();
        void insertMask(Entity entity, Systems::Mask mask);
        /*
        void askForInit();
        bool initEntitiesFromServer();
        */
        void sendReady();
        void lookForServer();

        const sf::Vector2f& getPlayerPosition() const;
        const sf::Vector2f& getCoPlayerPosition() const;

    private:

        State::Context& mContext;
        std::map<Entity, Systems::Mask> mMasks;
        std::vector<System*> mSystems;
        std::map<Entity, std::set<Entity> > mSons;
        std::map<Entity, Entity> mFathers;

        std::set<Entity> mEntitiesToDestroy;
        InputSystem mInputs;
        NetworkSystem mNetwork;
        LogicSystem mLogics;
        PhysicSystem mPhysics;
        GraphicSystem mGraphics;
        TimerSystem mTimers;
        WeaponSystem mWeapons;
        HealthSystem mHealth;
        ItemSystem mItems;
        ScoreSystem mScores;
        SoundSystem mSounds;
        AISystem mAi;


        Entity mPlayerID = 0;
        Entity mPlayerWeaponID = 1;
        Entity sensorOne = 0;

        Entity mCoPlayerID = 2;
        Entity mCoPlayerWeaponID = 3;
        Entity sensorTwo = 0;

        bool paddingRight = false;
};
