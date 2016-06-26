#pragma once
#include "system.h"
#include "../states/state.h"
#include <Box2D/Box2D.h>

#include <SFML/System.hpp>

class CollisionSystem: public System, public b2ContactListener
{
    public:

        CollisionSystem(World* world, State::Context context);
        virtual void update(sf::Time dt);

        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);

        void setNumFootContacts(int n);
        int getNumFootContacts();
        int getCoNumFootContacts();

    private:

        int mNumFootContacts;
        int mCoNumFootContacts;
};
