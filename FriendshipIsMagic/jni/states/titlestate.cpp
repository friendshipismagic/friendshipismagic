#include "titlestate.h"
#include <iostream>
#include <cmath>

TitleState::TitleState(StateStack& mystack, Context& context)
: State(mystack, context)
{
}

void TitleState::init()
{
    mTextEffectTime = sf::Time::Zero;
    mSettingsSprite.setTexture(*getContext().textures->get("icons/settings"));
    mBackgroundSprite.setTexture(*getContext().textures->get("menu/main/background"));
	mOnePlayerSprite.setTexture(*getContext().textures->get("OnePlayer"));
	mTwoPlayersSprite.setTexture(*getContext().textures->get("TwoPlayers"));
	updateRatio();

}

void TitleState::updateRatio() {

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

	mOnePlayerSprite.setScale(2,2);
	auto OP1rect = mOnePlayerSprite.getGlobalBounds();
	mOnePlayerSprite.setPosition(size.x/3-OP1rect.width/2,size.y/2-OP1rect.height/2);

	mTwoPlayersSprite.setScale(2,2);
	auto TP2rect = mTwoPlayersSprite.getGlobalBounds();
	mTwoPlayersSprite.setPosition(2*size.x/3-TP2rect.width/2,size.y/2-TP2rect.height/2);

	auto settingsRect = mSettingsSprite.getGlobalBounds();
	mSettingsSprite.setPosition(size.x/2. - settingsRect.width/2.,0);

}

bool TitleState::handleEvent(const sf::Event& event)
{
	
	//auto coords = getContext().window->mapPixelToCoords({x,y}, mView);
	//mBackgroundSprite.getGlobalBounds().contains(coords);
	//event.touch.y


    switch(event.type) {
        case sf::Event::TouchBegan:  //event.touch //
        case sf::Event::MouseButtonPressed:{

			sf::Vector2i coords_screen;
			if (event.type == sf::Event::TouchBegan) {
				std::cout << "touch" << std::endl;
				coords_screen.x = event.touch.x;
				coords_screen.y = event.touch.y;
			} else {
				coords_screen.x = event.mouseButton.x;
				coords_screen.y = event.mouseButton.y;
				std::cout << "mouse" << std::endl;
			}

			auto coords = getContext().window->mapPixelToCoords(coords_screen, mView);

			bool isSettingsButtonPressed = mSettingsSprite.getGlobalBounds().contains(coords);

			if(isSettingsButtonPressed){
				requestStackPop();
				requestStackPush(States::Settings);
				return true;
			}
        	requestStackPop();
			requestStackPush(States::Connect);
			break;
        }


        case sf::Event::Closed:
            requestStackPop();
            break;

		case sf::Event::Resized:
			updateRatio();
			break;
        default:
        	break;
    }
    return true;
}
bool TitleState::update(sf::Time dt)
{
    return true;
}

void TitleState::draw()
{
    mContext.window->draw(mBackgroundSprite);
    mContext.window->draw(mSettingsSprite);
	mContext.window->draw(mOnePlayerSprite);
	mContext.window->draw(mTwoPlayersSprite);
}
