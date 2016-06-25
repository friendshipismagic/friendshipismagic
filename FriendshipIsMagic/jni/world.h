#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "system.h"
#include "systemprovider.h"
#include "state.h"
#include "graphicsystem.h"
#include "inputsystem.h"
#include "timersystem.h"
#include "logicsystem.h"
#include "weaponsystem.h"
#include "healthsystem.h"
#include "itemsystem.h"
#include "scoresystem.h"
#include <Box2D/Box2D.h>
#include <set>
#include "entity.h"

class World
{
    public:

        World(State::Context context);
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

        Systems::Mask getMask(Entity entity);

        Entity getPlayerID() { return mPlayerID; };
        Entity getPlayerWeaponID() { return mPlayerWeaponID; };
        void setPlayerWeaponID(Entity entity) { mPlayerWeaponID = entity; };
        Entity getPlayerSensorID() { return sensorOne; };

        Entity getCoPlayerID() { return mCoPlayerID; };
        Entity getCoPlayerWeaponID() { return mCoPlayerWeaponID; };
        void setCoPlayerWeaponID(Entity entity) { mCoPlayerWeaponID = entity; };
        Entity getCoPlayerSensorID() { return sensorTwo; };

        void insertDependency(Entity entityFather, Entity entitySon);
        void deleteDependency(Entity entityFather, Entity entitySon);

        void createPlayer();
        void createCoPlayer();

        void insertMask(Entity entity, Systems::Mask mask);

    private:

        State::Context mContext;
        std::map<Entity, Systems::Mask> mMasks;
        std::vector<System*> mSystems;
        std::map<Entity, std::set<Entity> > mSons;
        std::map<Entity, Entity> mFathers;

        std::vector<Entity> mEntitiesToDestroy;
        GraphicSystem* mGraphics;
        TimerSystem* mTimers;
        PhysicSystem* mPhysics;
        InputSystem* mInputs;
        LogicSystem* mLogics;
        WeaponSystem* mWeapons;
        HealthSystem* mHealth;
        ItemSystem* mItems;
        ScoreSystem* mScores;

        Entity mPlayerID = 0;
        Entity mPlayerWeaponID = 1;
        Entity sensorOne = 0;

        Entity mCoPlayerID = 2;
        Entity mCoPlayerWeaponID = 3;
        Entity sensorTwo = 0;
};
