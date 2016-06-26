#pragma once
#include "system.h"
#include "../states/state.h"
#include "../entity.h"

class ScoreSystem: public System
{
    public:

        ScoreSystem(World* world, State::Context context);
        void update(sf::Time dt);
        int getScore(Entity entity);

        void insertScore(Entity entity, int score);
        void deleteScore(Entity entity);
        void addToScore(Entity entity, int amount);

    private:

        std::map<Entity, int> mScores;

};
