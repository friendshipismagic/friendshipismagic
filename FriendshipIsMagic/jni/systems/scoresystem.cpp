#include "scoresystem.h"
#include "../core/world.h"

ScoreSystem::ScoreSystem(World* world, State::Context context)
: System(world, context)
{

}

void ScoreSystem::update(sf::Time dt)
{

}

int ScoreSystem::getScore(Entity entity)
{
    assert(mScores.find(entity) != mScores.end());
    return mScores[entity];
}

void ScoreSystem::insertScore(Entity entity, int score)
{
    if (mScores.find(entity) == mScores.end())
        mScores.insert(std::make_pair(entity, score));
    else
        mScores[entity] = score;
}

void ScoreSystem::deleteScore(Entity entity)
{
    if (mScores.find(entity) != mScores.end())
        mScores.erase(entity);
}

void ScoreSystem::addToScore(Entity entity, int amount)
{
     if (mScores.find(entity) != mScores.end())
        mScores[entity] += amount;
}
