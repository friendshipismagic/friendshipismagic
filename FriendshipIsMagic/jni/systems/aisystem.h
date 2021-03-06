#pragma once
#include "system.h"
#include "../states/state.h"
#include "../ai/ai/aiinterface.h"
#include "../ai/matrix/matrix.h"
#include "physicsystem.h"
#include <set>

class AISystem: public System
{
    public:

         AISystem(World* world, State::Context context, PhysicSystem* physics);
         void update(sf::Time dt);

         AiInterface::Action getAction();

         void setMatrix(std::string tile, int n);
         void insertMonster(Entity entity);
         void deleteMonster(Entity entity);

    private:

        AiInterface mAI;
        AiInterface::Action action;
        Matrix mMatrix;
        PhysicSystem* mPhysics;
        std::set<Entity> mMonsters;

};
