#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "system.h"
#include "SystemProvider.h"
#include "State.h"
#include "GraphicSystem.h"

class World
{
    public:

        World(State::Context* context);
        void update(sf::Time dt);
        void draw();

        void setLeft(bool);
        void setRight(bool);
        void setJump(bool b) { jump = b;};
    private:

        std::vector<System*> mSystems;
        GraphicSystem* graphics;
        PhysicSystem* physics;
        bool right;
        bool left;
        bool jump;
        float x;

};
