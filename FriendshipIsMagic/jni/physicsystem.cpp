#include "physicsystem.h"
#include "bloc.h"
#include <functional>
#include "world.h"

PhysicSystem::PhysicSystem(World* world, State::Context context, InputSystem* inputs)
: mContext(context)
, mGameWorld(world)
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

    insertPosition(0, b2Vec2({mPlayer.getPos().x, mPlayer.getPos().y}));
    insertBody(0, mPlayer.getBody());

    b2Body* floor  = createBody(6, 5.2, 0.5f, 0.5f, 20, false);

    insertPosition(1, floor->GetPosition());
    insertBody(1, floor);

    b2Body* floor2 = createBody(3, 5.2, 0.5f, 0.5f, 0, false);
    floor2->SetType(b2_dynamicBody);

    insertPosition(2, floor2->GetPosition());
    insertBody(2, floor2);

    b2Body* floor3 = createBody(3, 6.5, 10.f, 0.5f, 0, false);

    insertPosition(3, floor3->GetPosition());
    insertBody(3, floor3);

    std::function<const sf::Vector2f&(unsigned int index)> posFunction = [this](unsigned int index) { return getPosition(index);};
    mPositionProvider = new PositionProvider(&posFunction);
}

void PhysicSystem::update(sf::Time dt)
{
    b2Body* mPlayerBody = mBodies[0];
    bool mRight = inputs->getInputState(Input::right);
    bool mLeft = inputs->getInputState(Input::left);
    bool mJump = inputs->getInputState(Input::jump);
    bool mFire = inputs->getInputState(Input::fire);

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
    if (mJump && jumpListener->getNumFootContacts()>=1)
    {
        mPlayerBody->SetAwake(true);
        mPlayerBody->ApplyLinearImpulse( b2Vec2(0, -mPlayerBody->GetMass()), mPlayerBody->GetWorldCenter(), true );
    }
    if (mFire)
    {
        mGameWorld->createEntity(Systems::BULLET,"");
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

void PhysicSystem::insertPosition(int entity, b2Vec2 pos)
{
    mPositions.insert(std::make_pair(entity, sf::Vector2f({pos.x, pos.y})));
}

b2Body* PhysicSystem::createBody(float x, float y, float width, float height, float rotation, bool isDynamic)
{
    b2BodyDef mBodyDef;
	mBodyDef.position.Set(x, y);
	mBodyDef.angle = (rotation);
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
    mBody->CreateFixture(&mFixtureDef);

    return mBody;
}

