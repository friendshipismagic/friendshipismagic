#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "system.h"
#include "state.h"
#include "player.h"
#include "systemprovider.h"
#include "collisionsystem.h"
#include "logicsystem.h"
#include "entity.h"

class World;

class PhysicSystem: public System
{
    public:

        PhysicSystem(World* world, State::Context context, LogicSystem* logics);
        virtual void update(sf::Time dt);
        const sf::Vector2f& getPosition(Entity entity);
        PositionProvider* getPositionProvider() { return mPositionProvider; };

        void insertPosition(Entity entity, b2Vec2 pos);
        void insertBody(Entity entity, b2Body* body);

        b2Body* createBody(Entity entity, float x, float y, float width, float height, float rotation, bool isDynamic);

        void addSensor(Entity entity, Entity sensorID);

        void deleteBody(Entity entity);
        void deletePosition(Entity entity);

        int getScale() { return mScale; };

        void mirror(Entity entity);

    private:

        LogicSystem* logics;
        b2World mWorld;
        int mScale;

        CollisionSystem* collisionListener;
        const sf::Vector2f errorPos;

        //Position component
        std::map<Entity, sf::Vector2f> mPositions;
        PositionProvider* mPositionProvider;

        //Body component
        std::map<Entity, b2Body*> mBodies;

        sf::Time mJumpTimer;
};
