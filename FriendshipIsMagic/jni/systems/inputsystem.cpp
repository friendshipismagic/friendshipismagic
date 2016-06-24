#include "inputsystem.h"
#include "../core/world.h"

InputSystem::InputSystem(World* world, State::Context& context)
: System(world, context)
, mInputs()
{
    mInputs.insert(std::make_pair(Input::jump, false));
    mInputs.insert(std::make_pair(Input::right, false));
    mInputs.insert(std::make_pair(Input::left, false));
    mInputs.insert(std::make_pair(Input::fire, false));

    mTouchTime.resize(10);
    mTouchPos.resize(10);
    mTouchInputs.resize(10);
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
        /*case sf::Event::TouchBegan:
            mTouchTime[event.touch.finger] = sf::Clock();
            mTouchPos[event.touch.finger] = mContext.window->mapPixelToCoords({event.touch.x, event.touch.y});
            break;
        case sf::Event::TouchEnded:
            mInputs[mTouchInputs[event.touch.finger]] = false;
            break;*/
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
    if (key==sf::Keyboard::X)
    {
        mInputs[Input::fire] = isPressed;
    }
}

void InputSystem::update(sf::Time dt)
{

}

bool InputSystem::getInputState(Input input)
{
    return mInputs[input];
}
