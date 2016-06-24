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
#include <Box2D/Box2D.h>

class World
{
    public:

        World(State::Context context);
        void update(sf::Time dt);
        void draw();
        void handleEvent(const sf::Event& event);

        int createEntity(Systems::Mask mask, std::string fileName, float x, float y);

        void destroyEntity(int entity);
        void sigDestroyEntity(int entity);
        void sigTimerCall(int entity);
        void sigCollisionWeaponItem(int entityPlayer, int entityItem);
        void sigCollisionBullet(int entityBullet, int entityVictim);
        void timerOn(int entity);

        Systems::Mask getMask(int entity);

        int getPlayerID() { return mPlayerID; };
        int getPlayerWeaponID() { return mPlayerWeaponID; };
        void setPlayerWeaponID(int entity) { mPlayerWeaponID = entity; };
        int getPlayerSensorID() { return sensorOne; };

        int getCoPlayerID() { return mCoPlayerID; };
        int getCoPlayerWeaponID() { return mCoPlayerWeaponID; };
        void setCoPlayerWeaponID(int entity) { mCoPlayerWeaponID = entity; };
        int getCoPlayerSensorID() { return sensorTwo; };

    private:

        State::Context mContext;
        std::vector<Systems::Mask> mMasks;
        std::vector<System*> mSystems;

        std::vector<int> mEntitiesToDestroy;
        GraphicSystem* graphics;
        TimerSystem* timers;
        PhysicSystem* physics;
        InputSystem* inputs;
        LogicSystem* logics;
        WeaponSystem* weapons;
        HealthSystem* health;

        int mPlayerID = 0;
        int mPlayerWeaponID = 1;
        int sensorOne = 0;

        int mCoPlayerID = 2;
        int mCoPlayerWeaponID = 3;
        int sensorTwo = 0;
};
