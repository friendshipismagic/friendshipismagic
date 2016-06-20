#include "PhysicSystem.h"

#include <functional>

const sf::Vector2f& PhysicSystem::getPosition(unsigned int index)
{
    if (index < mPositions.size())
        return mPositions[index];

    return errorPos;
}

PhysicSystem::PhysicSystem(State::Context* context)
: mContext(context)
, mWorld(b2Vec2{0.f,10.f})
, scale(10)
, mPlayer(&mWorld, 1, 1)
, errorPos(sf::Vector2f({-1, -1}))
, mPositions()
, mBodies()
{
    mPositions.push_back(mPlayer.getPos());
    mBodies.push_back(mPlayer.getBody());

    std::function<const sf::Vector2f&(unsigned int index)> posFunction = [this](unsigned int index) { return getPosition(index);};
    mPositionProvider = new PositionProvider(&posFunction);
}

void PhysicSystem::update(sf::Time dt)
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    mWorld.Step(timeStep, velocityIterations, positionIterations);

    for(unsigned int i = 0; i < mBodies.size(); i++)
    {
        b2Vec2 pos = mBodies[i]->GetPosition();
        mPositions[i] = sf::Vector2f({pos.x*scale, pos.y*scale});
    }
}


