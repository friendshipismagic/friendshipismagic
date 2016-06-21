#include "PhysicSystem.h"
#include "Bloc.h"
#include <functional>

PhysicSystem::PhysicSystem(State::Context* context, InputSystem* inputs)
: mContext(context)
, inputs(inputs)
, mWorld(b2Vec2{0.f,10.f})
, scale(100)
, mPlayer(&mWorld, 1, 1)
, errorPos(sf::Vector2f({-1, -1}))
, mPositions()
, mBodies()
{
    jumpListener = new MyContactListener();
    mWorld.SetContactListener(jumpListener);

    insertPosition(0, mPlayer.getPos());
    insertBody(0, mPlayer.getBody());

    Bloc floor(&mWorld, 1, 5, 0.5f, 0.5f, 20);

    insertPosition(1, floor.getPos());
    insertBody(1, floor.getBody());

    Bloc floor2(&mWorld, 3, 5, 0.5f, 0.5f, 0);

    insertPosition(2, floor2.getPos());
    insertBody(2, floor2.getBody());

    Bloc floor3(&mWorld, 5, 5, 0.5f, 0.5f, 0);

    insertPosition(3, floor3.getPos());
    insertBody(3, floor3.getBody());

    std::function<const sf::Vector2f&(unsigned int index)> posFunction = [this](unsigned int index) { return getPosition(index);};
    mPositionProvider = new PositionProvider(&posFunction);
}

void PhysicSystem::update(sf::Time dt)
{
    b2Body* mPlayerBody = mBodies[0];
    bool mRight = inputs->getInputState(Input::right);
    bool mLeft = inputs->getInputState(Input::left);
    bool mJump = inputs->getInputState(Input::jump);

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

const sf::Vector2f& PhysicSystem::getPosition(unsigned int index)
{
    if (index < mPositions.size())
        return mPositions[index];

    return errorPos;
}

void PhysicSystem::insertBody(int entity, b2Body* body)
{
    mBodies.insert(std::make_pair(entity, body));
}

void PhysicSystem::insertPosition(int entity, sf::Vector2f pos)
{
    mPositions.insert(std::make_pair(entity, pos));
}
