#include "collisionsystem.h"
#include "../core/world.h"

CollisionSystem::CollisionSystem(World* world, State::Context context)
: System(world, context)
, mNumFootContacts(0)
, mCoNumFootContacts(0)
{

}

void CollisionSystem::update(sf::Time dt)
{

}

void CollisionSystem::BeginContact(b2Contact* contact)
{
    Entity entityA = ((Entity) (contact->GetFixtureA()->GetUserData()));
    Entity entityB = ((Entity) (contact->GetFixtureB()->GetUserData()));
    Systems::Mask maskA = mGameWorld->getMask(entityA);
    Systems::Mask maskB = mGameWorld->getMask(entityB);

    if((maskA == Systems::Mask::BULLET) && (maskB != Systems::Mask::BULLET))
    {
        std::cout <<"collision " <<  entityA << std::endl;
        mGameWorld->sigCollisionBullet(entityA, entityB);
    }

    if((maskB == Systems::Mask::BULLET) && (maskA != Systems::Mask::BULLET))
    {
        std::cout <<"collision " <<  entityB << std::endl;
        mGameWorld->sigCollisionBullet(entityB, entityA);
    }

    if((maskA == Systems::Mask::PLAYER) && (maskB == Systems::Mask::ITEM))
    {
        mGameWorld->sigCollisionItem(entityA, entityB);
    }

    //check if fixture A was the foot sensor
    if ( entityA  == mGameWorld->getPlayerSensorID() )
        mNumFootContacts++;
    else if (entityA == mGameWorld->getCoPlayerSensorID())
         mCoNumFootContacts++;
    //check if fixture B was the foot sensor
     if ( entityB  == mGameWorld->getPlayerSensorID() )
        mNumFootContacts++;
    else if (entityB == mGameWorld->getCoPlayerSensorID())
         mCoNumFootContacts++;

    //std::cout << mNumFootContacts << std::endl;
}

void CollisionSystem::EndContact(b2Contact* contact)
{
    Entity entityA = ((Entity) (contact->GetFixtureA()->GetUserData()));
    Entity entityB = ((Entity) (contact->GetFixtureB()->GetUserData()));

    //check if fixture A was the foot sensor
    if ( entityA  == mGameWorld->getPlayerSensorID() )
        mNumFootContacts--;
    else if (entityA == mGameWorld->getCoPlayerSensorID())
         mCoNumFootContacts--;
    //check if fixture B was the foot sensor
     if ( entityB  == mGameWorld->getPlayerSensorID() )
        mNumFootContacts--;
    else if (entityB == mGameWorld->getCoPlayerSensorID())
         mCoNumFootContacts--;
}

int CollisionSystem::getNumFootContacts()
{
    return mNumFootContacts;
}

int CollisionSystem::getCoNumFootContacts()
{
    return mCoNumFootContacts;
}

void CollisionSystem::setNumFootContacts(int n)
{
    mNumFootContacts = n;
}
