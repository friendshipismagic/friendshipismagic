#pragma once
#include "system.h"
#include "state.h"

namespace Weapon
{
    enum Type {gun, uzi, bazooka};
}

class WeaponSystem: public System
{
    public:

        WeaponSystem(World* world, State::Context context);
        void update(sf::Time dt);

        std::string getWeaponType(int entity);
        void insertWeaponType(int entity, std::string weaponType);
        void deleteWeaponType(int entity);

        int getDamage(int entity);
        void insertDamage(int entity, int damage);
        void deleteDamage(int entity);

    private:

        std::map<int, std::string> mWeaponTypes;
        std::map<int, int> mDamages;

};
