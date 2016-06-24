#pragma once
#include "system.h"
#include "state.h"
#include "inputsystem.h"


enum Logic { moveRight, moveLeft, isJumping, fireOn, isFacingRight, isFacingLeft, canFire, changeDirection };

class LogicSystem: public System
{
     public:

         LogicSystem(World* world, State::Context context, InputSystem* inputs);
         void update(sf::Time dt);

         bool getLogic(Logic l);
         void insertLogic(Logic l, bool);
         void setLogic(Logic l, bool);

     private:

        InputSystem* mInputs;

        std::map<Logic, bool> mLogics;
};
