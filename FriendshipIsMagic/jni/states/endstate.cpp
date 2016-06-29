/*
 * endstate.cpp
 *
 *  Created on: 29 juin 2016
 *      Author: admin
 */

#include "endstate.h"
#include <iostream>

EndState::EndState(StateStack& mystack, Context& context)
: State(mystack, context)
{
	mFont = mContext.fonts->get("font");
	mText.setFont(*mFont);
	mText.setString("");
}

void EndState::init()
{
    mBackgroundSprite.setTexture(*getContext().textures->get("menu/main/background"));
	updateRatio();
	mText.setString("End of the level");
	mText.setPosition(100, 200);
}

void EndState::updateRatio()
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

bool EndState::handleEvent(const sf::Event& event)
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

        	requestStackPop();

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

bool EndState::update(sf::Time dt)
{
    return true;
}

void EndState::draw()
{
    mContext.window->draw(mBackgroundSprite);
}




