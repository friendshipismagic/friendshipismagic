#include "logicsystem.h"
#include "network-system.h"
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
	mLogics.insert(std::make_pair(Logic::coIsFacingLeft, true));
	mLogics.insert(std::make_pair(Logic::coIsFacingRight, false));
	mLogics.insert(std::make_pair(Logic::coCanFire, false));

    mLogics.insert(std::make_pair(Logic::coChangeDirection, false));
}

void LogicSystem::update(sf::Time dt)
{
	if(mContext.UDPMode == UDPAgent::Mode::Server){
		mLogics[Logic::moveRight] = mInputs->getInputState(Input::right);
		mLogics[Logic::moveLeft] = mInputs->getInputState(Input::left);
		mLogics[Logic::fireOn] = mInputs->getInputState(Input::fire);
		mLogics[Logic::isJumping] = mInputs->getInputState(Input::jump);

		//coPLayer
		bool oldCoIsFacingLeft = mLogics[Logic::coIsFacingLeft];
		mLogics[Logic::coFireOn] = mNetwork->getLogicState(Logic::fireOn);

		mLogics[Logic::coIsFacingLeft] = mNetwork->getLogicState(Logic::isFacingLeft);
		mLogics[Logic::coIsFacingRight] = mNetwork->getLogicState(Logic::isFacingRight);
		if(oldCoIsFacingLeft != mLogics[Logic::coIsFacingLeft])
			mLogics[Logic::coChangeDirection] = true;
		else
			mLogics[Logic::coChangeDirection] = false;
		oldCoIsFacingLeft = mLogics[Logic::coIsFacingLeft];


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

	}
	else if(mContext.UDPMode == UDPAgent::Mode::Client){
		//std::cout << " FireOn P1 : " << mNetwork->getLogicState(Logic::fireOn) << " FacingLeft : "<< mNetwork->getLogicState(Logic::isFacingLeft) << std::endl;
		bool oldIsFacingLeft = mLogics[Logic::isFacingLeft] ;
		mLogics[Logic::fireOn] = mNetwork->getLogicState(Logic::fireOn);
		mLogics[Logic::isFacingLeft] = mNetwork->getLogicState(Logic::isFacingLeft);
		mLogics[Logic::isFacingRight] = mNetwork->getLogicState(Logic::isFacingRight);
		if(oldIsFacingLeft != mLogics[Logic::isFacingLeft])
			mLogics[Logic::changeDirection] = true;
		else
			mLogics[Logic::changeDirection] = false;
		oldIsFacingLeft = mLogics[Logic::isFacingLeft];


		//coPLayer

		mLogics[Logic::coMoveRight] = mInputs->getInputState(Input::right);
		mLogics[Logic::coMoveLeft] = mInputs->getInputState(Input::left);
		mLogics[Logic::coFireOn] = mInputs->getInputState(Input::fire);
		mLogics[Logic::coIsJumping] = mInputs->getInputState(Input::jump);


		if (mLogics[Logic::coMoveRight] && !mLogics[Logic::coMoveLeft])
		{
			if (mLogics[Logic::coIsFacingLeft])
				mLogics[Logic::coChangeDirection] = true;
			else
				mLogics[Logic::coChangeDirection] = false;

			mLogics[Logic::coIsFacingLeft] = false;
			mLogics[Logic::coIsFacingRight] = true;
		}
		if (mLogics[Logic::coMoveLeft] && !mLogics[Logic::coMoveRight])
		{
			if (mLogics[Logic::coIsFacingRight])
				mLogics[Logic::coChangeDirection] = true;
			else
				mLogics[Logic::coChangeDirection] = false;

			mLogics[Logic::coIsFacingLeft] = true;
			mLogics[Logic::coIsFacingRight] = false;
		}
		if (mLogics[Logic::coMoveLeft] && mLogics[Logic::coMoveRight])
			mLogics[Logic::coChangeDirection] = false;
		if (!mLogics[Logic::coMoveLeft] && !mLogics[Logic::coMoveRight])
			mLogics[Logic::coChangeDirection] = false;
	}
	//Solo mode
	else{
		//TO DO implement inputs from AI P2
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
