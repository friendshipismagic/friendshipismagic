#pragma once
#include "system.h"
#include "state.h"
#include "graphicsystem.h"

class HealthSystem: public System
{
    public:

        HealthSystem(World* world, State::Context context, GraphicSystem* graphics);
        void update(sf::Time dt);

        int getCurrentHealth(int entity);
        void insertHealth(int entity, int health);
        void deleteHealth(int entity);
        void insertHealthBar(int entityOwner, int entityHealthBar);

        void addToHealth(int entity, int amount);

    private:

        std::map<int, int> mCurrentHealth;
        std::map<int, int> mMaxHealth;
        std::map<int, int> mHealthBarCorrelation;
        GraphicSystem* graphics;

};
