#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "system.h"
#include "SystemProvider.h"
#include "State.h"
#include "GraphicSystem.h"
#include "InputSystem.h"

class World
{
    public:

        World(State::Context* context);
        void update(sf::Time dt);
        void draw();
        void handleEvent(const sf::Event& event);

    private:

        std::vector<System*> mSystems;
        GraphicSystem* graphics;
        PhysicSystem* physics;
        InputSystem* inputs;

};
