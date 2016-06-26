#pragma once
#include "../states/state.h"
#include <SFML/Graphics.hpp>
#include "../states/statestack.h"

class Application
{
    public:

        Application(State::Context& context);

        void registerStates(State::Context& context);
        void processInput();
        void update(sf::Time dt);
        void draw();
        int run();

    private:

        StateStack mStateStack;
        sf::RenderWindow* mWindow;
};
