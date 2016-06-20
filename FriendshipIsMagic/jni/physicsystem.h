#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "system.h"
#include "state.h"
#include "player.h"
#include "systemprovider.h"
#include "mycontactlistener.h"

class PhysicSystem: public System
{
    public:

        PhysicSystem(State::Context* context);
        virtual void update(sf::Time dt);
        const sf::Vector2f& getPosition(unsigned int index);
        PositionProvider* getPositionProvider() { return mPositionProvider; };

    private:

        State::Context* mContext;
        b2World mWorld;
        int scale;
        Player mPlayer;
        MyContactListener* jumpListener;
        const sf::Vector2f errorPos;

        //Position component
        std::vector<sf::Vector2f> mPositions;
        PositionProvider* mPositionProvider;

        //Body component
        std::vector<b2Body*> mBodies;

    public:

        bool mRight;
        bool mLeft;
        bool mJump;

};
