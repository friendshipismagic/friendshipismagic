#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "system.h"
#include "systemprovider.h"
#include "state.h"
#include "graphicsystem.h"
#include "inputsystem.h"
#include <Box2D/Box2D.h>

class World
{
    public:

        World(State::Context context);
        void update(sf::Time dt);
        void draw();
        void handleEvent(const sf::Event& event);

        int createEntity(Systems::Mask mask, std::string fileName);

    private:

        std::vector<Systems::Mask> mMasks;
        std::vector<System*> mSystems;
        GraphicSystem * graphics;
        PhysicSystem* physics;
        InputSystem* inputs;

};