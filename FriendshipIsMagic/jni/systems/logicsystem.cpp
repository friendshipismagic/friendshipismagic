#include "logicsystem.h"
#include "../core/world.h"

LogicSystem::LogicSystem(World* world, State::Context& context, InputSystem* inputs, NetworkSystem* network)
: System(world, context)
, mInputs(inputs)
, mNetwork(network)
{
    mLogics.insert(std::make_pair(Logic::moveRight, false));
    mLogics.insert(std::make_pair(Logic::moveLeft, false));
    mLogics.insert(std::make_pair(Logic::fireOn, false));
    mLogics.insert(std::make_pair(Logic::isJumping, false));
    mLogics.insert(std::make_pair(Logic::isFacingLeft, true));
    mLogics.insert(std::make_pair(Logic::isFacingRight, false));
    mLogics.insert(std::make_pair(Logic::canFire, false));

    mLogics.insert(std::make_pair(Logic::changeDirection, false));


    //===== CoPLayer
    mLogics.insert(std::make_pair(Logic::coMoveRight, false));
	mLogics.insert(std::make_pair(Logic::coMoveLeft, false));
	mLogics.insert(std::make_pair(Logic::coFireOn, false));
	mLogics.insert(std::make_pair(Logic::coIsJumping, false));
	mLogics.insert(std::make_pair(Logic::coIsFacingLeft, false));
	mLogics.insert(std::make_pair(Logic::coIsFacingRight, false));
	mLogics.insert(std::make_pair(Logic::coCanFire, false));

}

void LogicSystem::update(sf::Time dt)
{
	if(mContext.UDPMode == UDPAgent::Mode::Server){
		mLogics[Logic::moveRight] = mInputs->getInputState(Input::right);
		mLogics[Logic::moveLeft] = mInputs->getInputState(Input::left);
		mLogics[Logic::fireOn] = mInputs->getInputState(Input::fire);
		mLogics[Logic::isJumping] = mInputs->getInputState(Input::jump);

		//coPLayer
		mLogics[Logic::coMoveRight] = mNetwork->getInputState(Input::right);
		mLogics[Logic::coMoveLeft] = mNetwork->getInputState(Input::left);
		mLogics[Logic::coFireOn] = mNetwork->getInputState(Input::fire);
		mLogics[Logic::coIsJumping] = mNetwork->getInputState(Input::jump);
	}else if(mContext.UDPMode == UDPAgent::Mode::Client){
		mLogics[Logic::moveRight] = mNetwork->getInputState(Input::right);
		mLogics[Logic::moveLeft] = mNetwork->getInputState(Input::left);
		mLogics[Logic::fireOn] = mNetwork->getInputState(Input::fire);
		mLogics[Logic::isJumping] = mNetwork->getInputState(Input::jump);
		//coPLayer
		mLogics[Logic::coMoveRight] = mInputs->getInputState(Input::right);
		mLogics[Logic::coMoveLeft] = mInputs->getInputState(Input::left);
		mLogics[Logic::coFireOn] = mInputs->getInputState(Input::fire);
		mLogics[Logic::coIsJumping] = mInputs->getInputState(Input::jump);
	}

    if (mLogics[Logic::moveRight] && !mLogics[Logic::moveLeft])
    {
        if (mLogics[Logic::isFacingLeft])
            mLogics[Logic::changeDirection] = true;
        else
            mLogics[Logic::changeDirection] = false;

        mLogics[Logic::isFacingLeft] = false;
        mLogics[Logic::isFacingRight] = true;
    }
    if (mLogics[Logic::moveLeft] && !mLogics[Logic::moveRight])
    {
        if (mLogics[Logic::isFacingRight])
            mLogics[Logic::changeDirection] = true;
        else
            mLogics[Logic::changeDirection] = false;

        mLogics[Logic::isFacingLeft] = true;
        mLogics[Logic::isFacingRight] = false;
    }
    if (mLogics[Logic::moveLeft] && mLogics[Logic::moveRight])
        mLogics[Logic::changeDirection] = false;
    if (!mLogics[Logic::moveLeft] && !mLogics[Logic::moveRight])
        mLogics[Logic::changeDirection] = false;




	if (mLogics[Logic::coMoveRight])
	{
		mLogics[Logic::coIsFacingLeft] = false;
		mLogics[Logic::coIsFacingRight] = true;
	}
	if (mLogics[Logic::coMoveLeft])
	{
		mLogics[Logic::coIsFacingLeft] = true;
		mLogics[Logic::coIsFacingRight] = false;
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
