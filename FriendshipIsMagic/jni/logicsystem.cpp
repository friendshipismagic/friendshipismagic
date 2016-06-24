#include "logicsystem.h"
#include "world.h"

LogicSystem::LogicSystem(World* world, State::Context context, InputSystem* inputs)
: System(world, context)
, mInputs(inputs)
{
    mLogics.insert(std::make_pair(Logic::moveRight, false));
    mLogics.insert(std::make_pair(Logic::moveLeft, false));
    mLogics.insert(std::make_pair(Logic::fireOn, false));
    mLogics.insert(std::make_pair(Logic::isJumping, false));
    mLogics.insert(std::make_pair(Logic::isFacingLeft, false));
    mLogics.insert(std::make_pair(Logic::isFacingRight, false));
    mLogics.insert(std::make_pair(Logic::canFire, false));
}

void LogicSystem::update(sf::Time dt)
{
    mLogics[Logic::moveRight] = mInputs->getInputState(Input::right);
    mLogics[Logic::moveLeft] = mInputs->getInputState(Input::left);
    mLogics[Logic::fireOn] = mInputs->getInputState(Input::fire);
    mLogics[Logic::isJumping] = mInputs->getInputState(Input::jump);

    if (mLogics[Logic::moveRight])
    {
        mLogics[Logic::isFacingLeft] = false;
        mLogics[Logic::isFacingRight] = true;
    }
    if (mLogics[Logic::moveLeft])
    {
        mLogics[Logic::isFacingLeft] = true;
        mLogics[Logic::isFacingRight] = false;
    }

}

bool LogicSystem::getLogic(Logic l)
{
    auto b = mLogics.find(l);
    assert(b != mLogics.end());
    return b->second;
}

void LogicSystem::setLogic(Logic l, bool b)
{
    mLogics[l] = b;
}
