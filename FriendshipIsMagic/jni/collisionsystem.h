#pragma once
#include "system.h"
#include "state.h"
#include <Box2D/Box2D.h>

class CollisionSystem: public System, public b2ContactListener
{
    public:

        CollisionSystem(World* world, State::Context context);
        void update(sf::Time dt);

        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);

        void setNumFootContacts(int n);
        int getNumFootContacts();

    private:

        int mNumFootContacts;
};
