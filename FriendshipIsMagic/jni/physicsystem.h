#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "system.h"
#include "state.h"
#include "player.h"
#include "systemprovider.h"
#include "collisionsystem.h"
#include "inputsystem.h"

class World;

class PhysicSystem: public System
{
    public:

        PhysicSystem(World* world, State::Context context, InputSystem* inputs);
        virtual void update(sf::Time dt);
        const sf::Vector2f& getPosition(unsigned int index);
        PositionProvider* getPositionProvider() { return mPositionProvider; };

        void insertPosition(int entity, b2Vec2 pos);
        void insertBody(int entity, b2Body* body);

        b2Body* createBody(int entity, float x, float y, float width, float height, float rotation, bool isDynamic);

        void addSensor(int entity, int sensorID);

        void deleteBody(int entity);
        void deletePosition(int entity);

    private:

        InputSystem* inputs;
        b2World mWorld;
        int scale;
<<<<<<< ea93cc0ac86dc2a23e1afc332e91c013ce57263a
        Player mPlayer;
        MyContactListener* jumpListener;
=======
        CollisionSystem* collisionListener;
>>>>>>> add CollisionSystem
        const sf::Vector2f errorPos;

        //Position component
        std::map<int, sf::Vector2f> mPositions;
        PositionProvider* mPositionProvider;

        //Body component
        std::map<int, b2Body*> mBodies;
};
