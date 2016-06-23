#include "physicsystem.h"
#include "bloc.h"
#include <functional>
#include "world.h"
#include "collisionsystem.h"

PhysicSystem::PhysicSystem(World* world, State::Context context, LogicSystem* logics, AISystem* ai)
: System(world, context)
, logics(logics)
, mAI(ai)
, mWorld(b2Vec2{0.f,10.f})
, scale(100)
, errorPos(sf::Vector2f({-1, -1}))
, mPositions()
, mBodies()
{
    collisionListener = new CollisionSystem(mGameWorld, mContext);
    mWorld.SetContactListener(collisionListener);

    std::function<const sf::Vector2f&(unsigned int index)> posFunction = [this](unsigned int index) { return getPosition(index);};
    mPositionProvider = new PositionProvider(&posFunction);
}

void PhysicSystem::update(sf::Time dt)
{
    b2Body* mPlayerBody = mBodies[mGameWorld->getPlayerID()];
    bool mRight = logics->getLogic(Logic::moveRight);
    bool mLeft = logics->getLogic(Logic::moveLeft);
    bool mJump = logics->getLogic(Logic::isJumping);
    bool mFire = logics->getLogic(Logic::fireOn);

    if (mRight)
    {
        mPlayerBody->SetAwake(true);
        b2Vec2 vel(mPlayerBody->GetLinearVelocity());
        vel.x = 2.5f;
        mPlayerBody->SetLinearVelocity(vel);
    }
    if (mLeft)
    {
        mPlayerBody->SetAwake(true);
        b2Vec2 vel(mPlayerBody->GetLinearVelocity());
        vel.x = -2.5f;
        mPlayerBody->SetLinearVelocity(vel);
    }
    if ((!mLeft && !mRight) || (mLeft && mRight))
    {
        b2Vec2 vel(mPlayerBody->GetLinearVelocity());
        vel.x = 0.;
        mPlayerBody->SetLinearVelocity(vel);
    }
    if (mJump && (collisionListener->getNumFootContacts() >= 1))
    {
        mPlayerBody->SetAwake(true);
        mPlayerBody->ApplyLinearImpulse( b2Vec2(0, -mPlayerBody->GetMass()), mPlayerBody->GetWorldCenter(), true );
    }
    if (mFire)
    {
        mGameWorld->createEntity(Systems::BULLET, "Entities/bullet.txt", mPlayerBody->GetPosition().x + 0.4, mPlayerBody->GetPosition().y);
    }

        logics->setLogic(Logic::canFire, false);
        mGameWorld->timerOn(mGameWorld->getPlayerWeaponID());
    }

    AiInterface::Action action = mAI->getAction();
    b2Body* mobody = mBodies[1];

    if (action == AiInterface::Action::left)
    {
        mobody->SetAwake(true);
        b2Vec2 vel(mobody->GetLinearVelocity());
        vel.x = 2.5f;
        mobody->SetLinearVelocity(vel);
    }
    if (action == AiInterface::Action::right)
    {
        mobody->SetAwake(true);
        b2Vec2 vel(mobody->GetLinearVelocity());
        vel.x = -2.5f;
        mobody->SetLinearVelocity(vel);
    }
    if (action == AiInterface::Action::still)
    {
        b2Vec2 vel(mPlayerBody->GetLinearVelocity());
        vel.x = 0.;
        mPlayerBody->SetLinearVelocity(vel);
    }
    if (action == AiInterface::Action::up)
    {
        mobody->SetAwake(true);
        mobody->ApplyLinearImpulse( b2Vec2(0, -mobody->GetMass()), mobody->GetWorldCenter(), true );
    }

    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    mWorld.Step(timeStep, velocityIterations, positionIterations);

    for(auto body: mBodies)
    {
        b2Vec2 pos = body.second->GetPosition();
        mPositions[body.first] = sf::Vector2f({pos.x*scale, pos.y*scale});
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

void PhysicSystem::insertPosition(int entity, b2Vec2 pos)
{
    mPositions.insert(std::make_pair(entity, sf::Vector2f({pos.x, pos.y})));
}

b2Body* PhysicSystem::createBody(int entity, float x, float y, float width, float height, float rotation, bool isDynamic)
{
    b2BodyDef mBodyDef;
	mBodyDef.position.Set(x, y);
	mBodyDef.angle = rotation;
	if (isDynamic)
        mBodyDef.type = b2_dynamicBody;

	b2PolygonShape mBox;
	mBox.SetAsBox(width, height);

	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &mBox;
	mFixtureDef.density = 0.0f;
	mFixtureDef.friction = 0.f;
	mFixtureDef.restitution = 0.f;

	b2Body* mBody = mWorld.CreateBody(&mBodyDef);

    b2Fixture* fixture = mBody->CreateFixture(&mFixtureDef);
    fixture->SetUserData((void*)entity);

    return mBody;
}

void PhysicSystem::addSensor(int entity, int sensorID)
{
    b2PolygonShape mBox;
    mBox.SetAsBox(0.06, 0.2, b2Vec2(0,0.3), 0);

	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &mBox;
	mFixtureDef.density = 0.0f;
	mFixtureDef.friction = 0.f;
	mFixtureDef.restitution = 0.f;
    mFixtureDef.isSensor = true;

    b2Fixture* footSensorFixture = mBodies[entity]->CreateFixture(&mFixtureDef);
    footSensorFixture->SetUserData( (void*)sensorID );
}

void PhysicSystem::deleteBody(int entity)
{
    b2Body* body = mBodies[entity];
    mWorld.DestroyBody(body);
    mBodies.erase(entity);
}


void PhysicSystem::deletePosition(int entity)
{
    mPositions.erase(entity);
}
