#pragma once
#include <SFML/Graphics.hpp>
#include "system.h"
#include "../states/state.h"
#include "systemprovider.h"

enum Input { idle, right, left, jump, fire };

class InputSystem: public System
{
    public:
        static constexpr int TIME_JUMP = 200;

        InputSystem(World* world, State::Context& context);
        virtual void update(sf::Time dt);
        void handleEvent(const sf::Event& event);
        bool getInputState(Input);

    private:

        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    private:

        std::vector<sf::Clock> mTouchTime;
        std::vector<sf::Vector2i> mTouchPos;
        std::vector<Input> mTouchInputs;
        std::map<Input, bool> mInputs;
};
