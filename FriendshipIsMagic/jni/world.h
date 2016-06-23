#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "system.h"
#include "systemprovider.h"
#include "state.h"
#include "graphicsystem.h"
#include "inputsystem.h"
#include "timersystem.h"
#include <Box2D/Box2D.h>

#include "aisystem.h"

#include "aisystem.h"

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

        Systems::Mask getMask(int entity);

        int levelReader(std::string fileName);

        int levelReader(std::string fileName);

    private:

        std::vector<Systems::Mask> mMasks;
        std::vector<System*> mSystems;

        std::vector<int> mEntitiesToDestroy;
        GraphicSystem* graphics;
        TimerSystem* timers;
        PhysicSystem* physics;
        InputSystem* inputs;
        AISystem* mAI;

        std::string tile = "";
        int mLineCount = 0;
        int mColumnCount = 0;

        AISystem* mAI;

        std::string tile = "";
        int mLineCount = 0;
        int mColumnCount = 0;

        int mCoPlayerID = 2;
        int mCoPlayerWeaponID = 3;
        int sensorTwo = 0;

        sf::View mGameView;
};
