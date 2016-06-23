#pragma once
#include "system.h"
#include "state.h"


class HealthSystem: public System
{
    public:

        HealthSystem(World* world, State::Context context);
        void update(sf::Time dt);

        int getCurrentHealth(int entity);
        void insertHealth(int entity, int health);
        void deleteHealth(int entity);

        void addToHealth(int entity, int amount);

    private:

        std::map<int, int> mCurrentHealth;
        std::map<int, int> mMaxHealth;

};
