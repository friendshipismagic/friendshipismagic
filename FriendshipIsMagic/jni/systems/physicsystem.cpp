#include "physicsystem.h"
#include <functional>
#include "../core/world.h"
#include "collisionsystem.h"
#include "logicsystem.h"

PhysicSystem::PhysicSystem(World* world, State::Context& context, LogicSystem* logics)
: System(world, context)
, logics(logics)
, mWorld(b2Vec2{0.f,10.f})
, mScale(100)
, errorPos(sf::Vector2f({-1000, -1000}))
, mPositions()
, mBodies()
{
    collisionListener = new CollisionSystem(mGameWorld, mContext);
    mWorld.SetContactListener(collisionListener);

    std::function<const sf::Vector2f&(unsigned int index)> posFunction = [this](unsigned int index) { return getPosition(index);};
    mPositionProvider = new PositionProvider(&posFunction);

    mJumpTimer = sf::Time::Zero;
}

void PhysicSystem::update(sf::Time dt)
{
    b2Body* mPlayerBody = mBodies[mGameWorld->getPlayerID()];
    bool mRight = logics->getLogic(Logic::moveRight);
    bool mLeft = logics->getLogic(Logic::moveLeft);
    bool mJump = logics->getLogic(Logic::isJumping);

    //==== CoPlayer
    b2Body* mCoPlayerBody = mBodies[mGameWorld->getCoPlayerID()];
	bool mCoRight = logics->getLogic(Logic::coMoveRight);
	bool mCoLeft = logics->getLogic(Logic::coMoveLeft);
	bool mCoJump = logics->getLogic(Logic::coIsJumping);

    mJumpTimer += dt;

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
    if (mJump && (collisionListener->getNumFootContacts() >= 1) && mJumpTimer.asSeconds() > 0.5)
    {
        mPlayerBody->SetAwake(true);
        mPlayerBody->ApplyLinearImpulse( b2Vec2(0, -mPlayerBody->GetMass()*6), mPlayerBody->GetWorldCenter(), true );
        mJumpTimer = sf::Time::Zero;
    }

    //===== CoPlayer
    if (mCoRight)
	{
		mCoPlayerBody->SetAwake(true);
		b2Vec2 vel(mCoPlayerBody->GetLinearVelocity());
		vel.x = 2.5f;
		mCoPlayerBody->SetLinearVelocity(vel);

		coIsFacingRight = true;
		coIsFacingLeft = false;
	}
	if (mCoLeft)
	{
		mCoPlayerBody->SetAwake(true);
		b2Vec2 vel(mCoPlayerBody->GetLinearVelocity());
		vel.x = -2.5f;
		mCoPlayerBody->SetLinearVelocity(vel);

		coIsFacingLeft = true;
		coIsFacingRight = false;
	}
	if ((!mCoLeft && !mCoRight) || (mCoLeft && mCoRight))
	{
		b2Vec2 vel(mCoPlayerBody->GetLinearVelocity());
		vel.x = 0.;
		mCoPlayerBody->SetLinearVelocity(vel);

	}
	if (mCoJump && (collisionListener->getCoNumFootContacts() >= 1) && mJumpTimer.asSeconds() > 0.5)
	{
		mCoPlayerBody->SetAwake(true);
		mCoPlayerBody->ApplyLinearImpulse( b2Vec2(0, -mCoPlayerBody->GetMass()*6), mCoPlayerBody->GetWorldCenter(), true );
		mJumpTimer = sf::Time::Zero;
	}

    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    mWorld.Step(timeStep, velocityIterations, positionIterations);

    for(auto body: mBodies)
    {
        b2Vec2 pos = body.second->GetPosition();
        mPositions[body.first] = sf::Vector2f({pos.x*mScale, pos.y*mScale});
    }
}

void PhysicSystem::syncPos(Entity entity){
		sf::Vector2f pos = mPositions[entity];
		mBodies[entity]->SetTransform(b2Vec2({pos.x/mScale, pos.y/mScale}), 0);


}

const sf::Vector2f& PhysicSystem::getPosition(Entity entity)
{
    if (mPositions.find(entity) != mPositions.end())
        return mPositions[entity];

    return errorPos;
}

void PhysicSystem::setPosition(Entity entity, sf::Vector2f pos)
{
    if (mPositions.find(entity) != mPositions.end())
         mPositions[entity] = pos;
}

void PhysicSystem::insertBody(Entity entity, b2Body* body)
{
    if(mBodies.find(entity) == mBodies.end())
        mBodies.insert(std::make_pair(entity, body));
    else
        mBodies[entity] = body;
}

void PhysicSystem::insertPosition(Entity entity, b2Vec2 pos)
{
    if(mPositions.find(entity) == mPositions.end())
        mPositions.insert(std::make_pair(entity, sf::Vector2f({pos.x, pos.y})));
    else
        mPositions[entity] = sf::Vector2f({pos.x, pos.y});
}

b2Body* PhysicSystem::createBody(Entity entity, float x, float y, float width, float height, float rotation, bool isDynamic, bool isSensor)
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
    mFixtureDef.isSensor = isSensor;

	b2Body* mBody = mWorld.CreateBody(&mBodyDef);

    b2Fixture* fixture = mBody->CreateFixture(&mFixtureDef);
    fixture->SetUserData((void*)entity);

    return mBody;
}

void PhysicSystem::addSensor(Entity entity, Entity owner, float x, float y, float w, float h)
{
    b2PolygonShape mBox;
    mBox.SetAsBox(w, h, b2Vec2(x,y), 0);

	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &mBox;
	mFixtureDef.density = 0.0f;
	mFixtureDef.friction = 0.f;
	mFixtureDef.restitution = 0.f;
    mFixtureDef.isSensor = true;

    b2Fixture* footSensorFixture = mBodies[owner]->CreateFixture(&mFixtureDef);
    footSensorFixture->SetUserData( (void*)(entity));
}

void PhysicSystem::deleteBody(Entity entity)
{
    if (mBodies.find(entity) != mBodies.end())
    {
        b2Body* body = mBodies[entity];
        mWorld.DestroyBody(body);
        mBodies.erase(entity);
    }
}


void PhysicSystem::deletePosition(Entity entity)
{
    if(mPositions.find(entity) != mPositions.end())
        mPositions.erase(entity);
}

void PhysicSystem::mirror(Entity entity)
{
    if(mPositions.find(entity) != mPositions.end())
    {
        sf::Vector2f pos = mPositions[entity];
        mPositions[entity] = sf::Vector2f({-pos.x, pos.y});
    }
}

void PhysicSystem::mirrorVelocity(Entity entity)
{
    if(mBodies.find(entity) != mBodies.end())
    {
        b2Body* body = mBodies[entity];
        b2Vec2 vel = body->GetLinearVelocity();
        body->SetLinearVelocity(b2Vec2({-vel.x, vel.y}));
    }
}
