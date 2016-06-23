#pragma once
#include "system.h"
#include "state.h"
#include "ai/ai/aiinterface.h"
#include "ai/matrix/matrix.h"

class AISystem: public System
{
    public:

         AISystem(World* world, State::Context context);
         void update(sf::Time dt);

         AiInterface::Action getAction();

         void setMatrix(std::string tile, int n);

    private:

        AiInterface mAI;
        AiInterface::Action action;
        Matrix mMatrix;

};
