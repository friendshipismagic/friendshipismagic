#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "System.h"
#include "State.h"
#include "Player.h"
#include "SystemProvider.h"
#include "myContactListener.h"
#include "InputSystem.h"

class PhysicSystem: public System
{
    public:

        PhysicSystem(State::Context* context, InputSystem* inputs);
        virtual void update(sf::Time dt);
        const sf::Vector2f& getPosition(unsigned int index);
        PositionProvider* getPositionProvider() { return mPositionProvider; };

    private:

        State::Context* mContext;
        InputSystem* inputs;
        b2World mWorld;
        int scale;
        Player mPlayer;
        MyContactListener* jumpListener;
        const sf::Vector2f errorPos;

        //Position component
        std::map<int, sf::Vector2f> mPositions;
        void insertPosition(int entity, sf::Vector2f pos);
        PositionProvider* mPositionProvider;

        //Body component
        std::map<int, b2Body*> mBodies;
        void insertBody(int entity, b2Body* body);
};
