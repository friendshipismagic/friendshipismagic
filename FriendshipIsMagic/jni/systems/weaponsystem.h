#pragma once
#include "system.h"
#include "../states/state.h"
#include "../core/entity.h"

namespace Weapon
{
    enum Type {gun, uzi, bazooka};
}

class WeaponSystem: public System
{
    public:

        WeaponSystem(World* world, State::Context& context);
        void update(sf::Time dt);

        std::string getWeaponType(Entity entity);
        void insertWeaponType(Entity entity, std::string weaponType);
        void deleteWeaponType(Entity entity);

        int getDamage(Entity entity);
        void insertDamage(Entity entity, int damage);
        void deleteDamage(Entity entity);

        Entity getOwner(Entity entity);
        void insertOwner(Entity entity, Entity owner);
        void deleteOwner(Entity entity);
        Entity getWeaponID(std::string weaponType);
    private:

        std::map<Entity, std::string> mWeaponTypes;
        std::map<Entity, int> mDamages;
        std::map<Entity, Entity> mBulletOwner;
};
