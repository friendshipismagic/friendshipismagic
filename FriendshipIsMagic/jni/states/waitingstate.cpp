#include "waitingstate.h"
#include <iostream>
#include <cmath>

WaitingState::WaitingState(StateStack& mystack, Context& context)
: State(mystack, context)
{
    mText.setFont(*context.fonts->get("font"));

    if(mContext.UDPMode = UDPAgent::Mode::Client)
        mText.setString("Waiting for a client");
    else
        mText.setString("Waiting for an host");

    mText.setPosition(200, 200);
}

void WaitingState::init()
{

    mBackgroundSprite.setTexture(*getContext().textures->get("menu/main/background"));
    /*
    if(mContext.UDPMode == UDPAgent::Mode::Server){
        //mText.setString("Waiting for a client");
        std::cout << "server waiting............"<< std::endl;
    }
    else if(mContext.UDPMode == UDPAgent::Mode::Client){
    	std::cout << "client waiting............"<< std::endl;
        //mText.setString("Waiting for an host");
    }
    else
    	mText.setString("Neither server or client. ERROR");
    */
	updateRatio();
}

void WaitingState::updateRatio()
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

bool WaitingState::handleEvent(const sf::Event& event)
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

           // requestStackPop();
           // requestStackPush(States::Game);
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

bool WaitingState::update(sf::Time dt)
{
	//std::cout << "waiting state update with mode"<< mContext.UDPMode << std::endl;
	if(mContext.foundPlayer){
		std::cout << "found!"<< std::endl;
		requestStackPop();
		//requestStackPush(States::Game);
	}
    return true;
}

void WaitingState::draw()
{
    mContext.window->draw(mBackgroundSprite);
    mContext.window->draw(mText);
}
