#pragma once
#include "system.h"
#include "../states/state.h"
#include "graphicsystem.h"
#include "../core/entity.h"

class HealthSystem: public System
{
    public:

        HealthSystem(World* world, State::Context& context, GraphicSystem* graphics);
        void update(sf::Time dt);

        int getCurrentHealth(Entity entity);
        int getMaxHealth(Entity entity);
        void insertHealth(Entity entity, int health);
        void deleteHealth(Entity entity);
        void insertHealthBar(Entity entityOwner, Entity entityHealthBar);

        void addToHealth(Entity entity, int amount);
        std::map<Entity, int> getCurrentHealth(){return mCurrentHealth;};
	   std::map<Entity, int> getMaxHealth(){return mMaxHealth;};
    private:

        std::map<Entity, int> mCurrentHealth;
        std::map<Entity, int> mMaxHealth;
        std::map<Entity, int> mHealthBarCorrelation;
        GraphicSystem* graphics;

};