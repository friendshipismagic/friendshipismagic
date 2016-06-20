#pragma once
#include <Box2D/Box2D.h>

class MyContactListener : public b2ContactListener
{
    public:
        void BeginContact(b2Contact* contact)
        {
            //check if fixture A was the foot sensor
            void* fixtureUserData = contact->GetFixtureA()->GetUserData();
            if ( (int)fixtureUserData == 3 )
                mNumFootContacts++;
            //check if fixture B was the foot sensor
            fixtureUserData = contact->GetFixtureB()->GetUserData();
            if ( (int)fixtureUserData == 3 )
                mNumFootContacts++;
        }

        void EndContact(b2Contact* contact)
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

        void setNumFootContacts(int n)
        {
            mNumFootContacts = n;
        }
        int getNumFootContacts()
        {
            return mNumFootContacts;
        }
    private:
        int mNumFootContacts = 0;
};
