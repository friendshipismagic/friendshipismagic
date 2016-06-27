#pragma once
#include "system.h"
#include "../states/state.h"

#include "../core/entity.h"
//#include "graphicsystem.h"

class GraphicSystem;

class HealthSystem: public System
{
    public:
		using health_t = sf::Uint16;
        HealthSystem(World* world, State::Context& context, GraphicSystem* graphics);
        void update(sf::Time dt);

        health_t getCurrentHealth(Entity entity);
        health_t getMaxHealth(Entity entity);
        void insertHealth(Entity entity, health_t health);
        void deleteHealth(Entity entity);
        void insertHealthBar(Entity entityOwner, Entity entityHealthBar);

        void addToHealth(Entity entity, int amount);
        std::map<Entity, health_t>& getCurrentHealth(){return mCurrentHealth;};
        std::map<Entity, health_t>& getMaxHealth(){return mMaxHealth;};
        void setCurrentHealth(Entity entity, health_t hp);
        void setMaxHealth(Entity entity, health_t maxHp);
    private:

        std::map<Entity, health_t> mCurrentHealth;
        std::map<Entity, health_t> mMaxHealth;
        std::map<Entity, health_t> mHealthBarCorrelation;
        GraphicSystem* graphics;

};
