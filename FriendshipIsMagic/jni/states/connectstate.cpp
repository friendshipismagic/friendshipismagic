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
	updateRatio();
}

void ConnectState::updateRatio()
{
	const float WORLD_HEIGHT = 1080;

    auto screenSize = getContext().window->getSize();
	auto ratio = screenSize.x / static_cast<float>(screenSize.y);
	mView.setSize(WORLD_HEIGHT, WORLD_HEIGHT); // no deformations
    //sf::Vector2f screenSize = mView.getSize();

	auto size = mView.getSize();

	auto bgRect  = mBackgroundSprite.getLocalBounds();
	auto bgScale = std::max(size.x/bgRect.width, size.y/bgRect.height);
	auto bgSize  = sf::Vector2f(bgRect.width*bgScale, bgRect.height*bgScale);
	auto bgShift = sf::Vector2f((size.x-bgSize.x)/2, (size.y-bgSize.y)/2);
	mBackgroundSprite.setScale(bgScale,bgScale);
	mBackgroundSprite.setPosition(bgShift);

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
        	requestStackPop();
        	requestStackPush(States::Game);
			requestStackPush(States::Waiting);
			break;
		}

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
}
