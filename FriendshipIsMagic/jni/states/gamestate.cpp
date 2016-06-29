#include "gamestate.h"

GameState::GameState(StateStack& mystack, State::Context& context)
: State(mystack, context)
, mFont()
, mText()
, mWorld(context)
{
    mFont = mContext.fonts->get("font");
    mText.setFont(*mFont);
    mText.setPosition(250.,300.);
    mText.setString("GameState! Yeah!");
}

void GameState::init()
{
	if(mContext.UDPMode == UDPAgent::Mode::Client){
		//mWorld.startUDPClient(UDPAgent::DEFAULT_PORT+1, "localhost", UDPAgent::DEFAULT_PORT );
		//std::cout << "gameState: started as Client." << std::endl;
		//mWorld.askForInit();
		//mWorld.sendReady();
		//mWorld.lookForServer();
	}
	else if(mContext.UDPMode == UDPAgent::Mode::Server){


	}
	else{
		std::cout << "gameState: no mode found for UDPAgent, launching solo mode." << std::endl;
	}
	//mWorld.initEntities();

}

bool GameState::handleEvent(const sf::Event& event)
{
    mWorld.handleEvent(event);

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
    mWorld.update(dt);
    if(getContext().UDPMode == UDPAgent::Server)
    	mView.setCenter(mWorld.getPlayerPosition());
    else if(getContext().UDPMode == UDPAgent::Client)
    	mView.setCenter(mWorld.getCoPlayerPosition());
    else
    	mView.setCenter(mWorld.getPlayerPosition());
    mView.setSize(590,590);
    return true;
}

void GameState::draw()
{
    getContext().window->setView(mView);
    mWorld.draw();
}
