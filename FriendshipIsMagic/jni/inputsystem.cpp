#include "InputSystem.h"

InputSystem::InputSystem(State::Context* context)
: mContext(context)
, mInputs()
{
    mInputs.insert(std::make_pair(Input::jump, false));
    mInputs.insert(std::make_pair(Input::right, false));
    mInputs.insert(std::make_pair(Input::left, false));

}

void InputSystem::handleEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        default:
            break;
    }
}

void InputSystem::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key==sf::Keyboard::Right)
    {
        mInputs[Input::right] = isPressed;
    }
    if (key==sf::Keyboard::Left)
    {
        mInputs[Input::left] = isPressed;
    }
    if (key==sf::Keyboard::Space)
    {
        mInputs[Input::jump] = isPressed;
    }
}

void InputSystem::update(sf::Time dt)
{

}

bool InputSystem::getInputState(Input input)
{
    return mInputs[input];
}
