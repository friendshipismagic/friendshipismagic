#include "PhysicSystem.h"
#include "Bloc.h"
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
, scale(100)
, mPlayer(&mWorld, 1, 1)
, errorPos(sf::Vector2f({-1, -1}))
, mPositions()
, mBodies()
, mRight(false)
, mLeft(false)
, mJump(false)
{
    jumpListener = new MyContactListener();
    mWorld.SetContactListener(jumpListener);

    mPositions.push_back(mPlayer.getPos());
    mBodies.push_back(mPlayer.getBody());

    Bloc floor(&mWorld, 1, 5);

    mPositions.push_back(floor.getPos());
    mBodies.push_back(floor.getBody());

    Bloc floor2(&mWorld, 3, 5);

    mPositions.push_back(floor2.getPos());
    mBodies.push_back(floor2.getBody());

    Bloc floor3(&mWorld, 5, 5);

    mPositions.push_back(floor3.getPos());
    mBodies.push_back(floor3.getBody());

    std::function<const sf::Vector2f&(unsigned int index)> posFunction = [this](unsigned int index) { return getPosition(index);};
    mPositionProvider = new PositionProvider(&posFunction);
}

void PhysicSystem::update(sf::Time dt)
{
    b2Body* mPlayerBody = mBodies[0];

    if (mRight)
    {
        mPlayerBody->SetAwake(true);
        b2Vec2 vel(mPlayerBody->GetLinearVelocity());
        vel.x = 2.;
        mPlayerBody->SetLinearVelocity(vel);
    }
    if (mLeft)
    {
        mPlayerBody->SetAwake(true);
        b2Vec2 vel(mPlayerBody->GetLinearVelocity());
        vel.x = -2.;
        mPlayerBody->SetLinearVelocity(vel);
    }
    if ((!mLeft && !mRight) || (mLeft && mRight))
    {
        b2Vec2 vel(mPlayerBody->GetLinearVelocity());
        vel.x = 0.;
        mPlayerBody->SetLinearVelocity(vel);
    }
    if (mJump && jumpListener->getNumFootContacts()>=1)
    {
        mPlayerBody->SetAwake(true);
        mPlayerBody->ApplyLinearImpulse( b2Vec2(0, -mPlayerBody->GetMass()), mPlayerBody->GetWorldCenter(), true );
    }

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


