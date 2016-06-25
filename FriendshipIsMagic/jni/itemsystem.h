#pragma once
#include "system.h"
#include "state.h"
#include "entity.h"

enum ItemType { none, weapon, swapstuff};

class ItemSystem: public System
{
    public:

        ItemSystem(World* world, State::Context context);
        void update(sf::Time dt);
        ItemType getType(Entity entity);

        void insertType(Entity entity, ItemType type);
        void deleteType(Entity entity);

        ItemType fromString(std::string type);

    private:

        std::map<Entity, ItemType> mTypes;

};
