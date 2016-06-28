#include "inputsystem.h"
#include "../core/world.h"
#include <SFML/Window.hpp>

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
        case sf::Event::TouchBegan:
            if (mTouchTime[event.touch.finger].getElapsedTime().asMilliseconds() < TIME_JUMP) {
                mInputs[Input::jump] = true;
            } else mInputs[Input::jump] = false;
            mTouchTime[event.touch.finger] = sf::Clock();
            mTouchPos[event.touch.finger] = {event.touch.x, event.touch.y};
            break;
        case sf::Event::TouchEnded:
            mInputs[mTouchInputs[event.touch.finger]] = false;
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
    if (key==sf::Keyboard::X)
    {
        mInputs[Input::fire] = isPressed;
    }
}

void InputSystem::update(sf::Time dt)
{
    auto wsize = mContext.window->getSize();

    for(int i=0; i<3; ++i) {
        if (!sf::Touch::isDown(i)) continue;
        auto touchPos = sf::Touch::getPosition(i, *mContext.window);
        if (touchPos.x < wsize.x/2 && mTouchTime[i].getElapsedTime().asMilliseconds() > TIME_JUMP) {
            mInputs[Input::fire] = true;
            mTouchInputs[i] = Input::fire;
        } else {
            mInputs[Input::fire] = false;
            //mTouchInputs[i] = Input::idle;
        }

        if (touchPos.x > wsize.x/2) {
            if (touchPos.x < mTouchPos[i].x) {
                mInputs[Input::left] = true;
                mInputs[Input::right] = false;
                mTouchInputs[i] = Input::left;
            }
            else {
                mInputs[Input::left] = false;
                mInputs[Input::right] = true;
                mTouchInputs[i] = Input::right;
            }

        }
    }
}

bool InputSystem::getInputState(Input input)
{
    return mInputs[input];
}
