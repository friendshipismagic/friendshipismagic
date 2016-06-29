#include "gamestate.h"

GameState::GameState(StateStack& mystack, State::Context& context)
: State(mystack, context)
, mFont()
, mText()
, mGameTime(sf::Time::Zero)
{
    mWorld.reset(new World(mContext));
}

void GameState::init()
{
    mWorld.reset(new World(mContext));
    mGameTime = sf::Time::Zero;

	if(mContext.UDPMode == UDPAgent::Mode::Client){
		//mWorld->startUDPClient(UDPAgent::DEFAULT_PORT+1, "localhost", UDPAgent::DEFAULT_PORT );
		std::cout << "gameState: started as Client." << std::endl;
		//mWorld->askForInit();
		//mWorld->sendReady();
		//mWorld->lookForServer();
	}
	else if(mContext.UDPMode == UDPAgent::Mode::Server){
		std::cout << "gameState: started as Server." << std::endl;

	}
	else if(mContext.UDPMode == UDPAgent::Solo){
		std::cout << "gameState: started as solo mode." << std::endl;
		mWorld->initEntities();
	}
	else{

	}
	//mWorld->initEntities();

}

bool GameState::handleEvent(const sf::Event& event)
{
    mWorld->handleEvent(event);
    #ifdef ANDROID_BUILD
    if (event.type == sf::Event::KeyPressed) {
            requestStackPop();
            requestStackPush(States::Title);
    }
    #endif 

    if(event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            requestStackPop();
        }
    }

    if(event.type == sf::Event::Closed){

    	requestStackPop();
    }

    return true;
}

bool GameState::update(sf::Time dt)
{
    mWorld->update(dt);

    if(getContext().UDPMode == UDPAgent::Server)
    	mView.setCenter(mWorld->getPlayerPosition());
    else if(getContext().UDPMode == UDPAgent::Client)
    	mView.setCenter(mWorld->getCoPlayerPosition());
    else// if (getContext().UDPMode == UDPAgent::Solo)
    	mView.setCenter(mWorld->getPlayerPosition());

    mView.setSize(590,590);

	mGameTime += dt;
	if(mGameTime.asSeconds() > 60)
	{
		requestStackPop();
		requestStackPush(States::End);
	}

    return true;
}

void GameState::draw()
{
    getContext().window->setView(mView);
    mWorld->draw();
}
