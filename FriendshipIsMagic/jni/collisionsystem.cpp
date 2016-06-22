#include "collisionsystem.h"
#include "world.h"

CollisionSystem::CollisionSystem(World* world, State::Context context)
: System(world, context)
, mNumFootContacts(0)
{

}

void CollisionSystem::update(sf::Time dt)
{

}

void CollisionSystem::BeginContact(b2Contact* contact)
{
    int entityA = ((int) (contact->GetFixtureA()->GetUserData()));
    int entityB = ((int) (contact->GetFixtureB()->GetUserData()));
    Systems::Mask maskA = mGameWorld->getMask(entityA);
    Systems::Mask maskB = mGameWorld->getMask(entityB);

    if((maskA == Systems::Mask::BULLET) && (maskB != Systems::Mask::BULLET))
        mGameWorld->sigDestroyEntity(entityA);

    if((maskB == Systems::Mask::BULLET) && (maskA != Systems::Mask::BULLET))
        mGameWorld->sigDestroyEntity(entityB);

    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( (int)fixtureUserData == 3 )
        mNumFootContacts++;
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( (int)fixtureUserData == 3 )
        mNumFootContacts++;
}

void CollisionSystem::EndContact(b2Contact* contact)
{
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( (int)fixtureUserData == 3 )
        mNumFootContacts--;
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( (int)fixtureUserData == 3 )
        mNumFootContacts--;
}

int CollisionSystem::getNumFootContacts()
{
    return mNumFootContacts;
}

void CollisionSystem::setNumFootContacts(int n)
{
    mNumFootContacts = n;
}
