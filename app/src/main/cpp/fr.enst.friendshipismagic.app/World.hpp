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
    private:

        std::vector<System*> mSystems;
        GraphicSystem* graphics;

};
