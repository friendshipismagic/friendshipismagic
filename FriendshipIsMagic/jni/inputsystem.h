#pragma once
#include <SFML/Graphics.hpp>
#include "system.h"
#include "state.h"
#include "systemprovider.h"

class World;

enum Input { right, left, jump, fire };

class InputSystem: public System
{
    public:

        InputSystem(World* world, State::Context context);
        virtual void update(sf::Time dt);
        void handleEvent(const sf::Event& event);
        bool getInputState(Input);

    private:

        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    private:

        std::map<Input, bool> mInputs;
};
