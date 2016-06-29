#include "connectstate.h"
#include <iostream>
#include <cmath>

ConnectState::ConnectState(StateStack& mystack, Context& context)
: State(mystack, context)
{

}

void ConnectState::init()
{
    mBackgroundSprite.setTexture(*getContext().textures->get("menu/main/background"));
    mServerModeSprite.setTexture(*getContext().textures->get("host"));
    mClientModeSprite.setTexture(*getContext().textures->get("join"));
	updateRatio();
}

void ConnectState::updateRatio()
{
    auto screenSize = getContext().window->getSize();

    sf::FloatRect screen(0,0,screenSize.x, screenSize.y) ;
    mView = sf::View(screen);
	auto size = mView.getSize();

	auto bgRect  = mBackgroundSprite.getLocalBounds();
	auto bgScale = std::max(size.x/bgRect.width, size.y/bgRect.height);
    mBackgroundSprite.setOrigin(bgRect.width/2., bgRect.height/2.);
	mBackgroundSprite.setScale(bgScale,bgScale);
	mBackgroundSprite.setPosition(size.x/2., size.y/2.);

	mServerModeSprite.setScale(2,2);
	auto serverRect = mServerModeSprite.getLocalBounds();
    mServerModeSprite.setOrigin(serverRect.width/2., serverRect.height/2.);
	mServerModeSprite.setPosition(size.x/3.,size.y/2.);

	mClientModeSprite.setScale(2,2);
	auto clientRect = mServerModeSprite.getLocalBounds();
    mClientModeSprite.setOrigin(clientRect.width/2, clientRect.height/2);
	mClientModeSprite.setPosition(2*size.x/3.,size.y/2.);

}

bool ConnectState::handleEvent(const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::TouchBegan:  //event.touch //
        case sf::Event::MouseButtonPressed:
        {

			//if SettingsButton is pressed go to
			sf::Vector2i coords_screen;
			if (event.type == sf::Event::TouchBegan)
                {
				std::cout << "touch" << std::endl;
				coords_screen.x = event.touch.x;
				coords_screen.y = event.touch.y;
			}
			else
			{
				coords_screen.x = event.mouseButton.x;
				coords_screen.y = event.mouseButton.y;
				std::cout << "mouse" << std::endl;
			}

			auto coords = getContext().window->mapPixelToCoords(coords_screen, mView);

			bool isServerButtonPressed = mServerModeSprite.getGlobalBounds().contains(coords);
			bool isClientButtonPressed = mClientModeSprite.getGlobalBounds().contains(coords);

			if(isServerButtonPressed){
				mContext.UDPMode = UDPAgent::Mode::Server;
				std::cout << "Server selected from connectState" << std::endl;
				requestStackPop();
				requestStackPush(States::Game);
				requestStackPush(States::Waiting);
				return true;
			}
			if(isClientButtonPressed){
				mContext.UDPMode = UDPAgent::Mode::Client;
				std::cout << "Client selected from connectState" << std::endl;
				requestStackPop();
				requestStackPush(States::Game);
				requestStackPush(States::Waiting);
				return true;
			}

			//auto coords = getContext().window->mapPixelToCoords(coords_screen, mView);
/*
			//Server
        	if (event.mouseButton.button == sf::Mouse::Left)
            {
        		mContext.UDPMode = UDPAgent::Mode::Server;
        		std::cout << "Server selected from connectState" << std::endl;
        	}
        	else if(event.mouseButton.button == sf::Mouse::Right)
        	{
        		mContext.UDPMode = UDPAgent::Mode::Client;
        		std::cout << "Client selected from connectState" << std::endl;

        	}
*/

			break;
		}

        case sf::Event::KeyPressed:
            requestStackPop();
            requestStackPush(States::Title);
            break;

        case sf::Event::Closed:
            requestStackPop();
            break;

		case sf::Event::Resized:
			updateRatio();
        default:
        	break;
    }
    return true;
}

bool ConnectState::update(sf::Time dt)
{
    return true;
}

void ConnectState::draw()
{
    mContext.window->draw(mBackgroundSprite);
	mContext.window->draw(mServerModeSprite);
	mContext.window->draw(mClientModeSprite);
}
