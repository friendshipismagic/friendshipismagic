#pragma once
#include <SFML/Graphics.hpp>
#include "System.h"
#include "State.h"
#include "SystemProvider.h"


enum Input { right, left, jump, fire };

class InputSystem: public System
{
    public:

        InputSystem(State::Context context);
        virtual void update(sf::Time dt);
        void handleEvent(const sf::Event& event);
        bool getInputState(Input);

    private:

        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    private:

        State::Context mContext;
        std::map<Input, bool> mInputs;
};
