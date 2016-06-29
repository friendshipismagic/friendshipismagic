#include "titlestate.h"
#include <iostream>
#include <cmath>

TitleState::TitleState(StateStack& mystack, Context& context)
: State(mystack, context)
{
}

void TitleState::init()
{
	std::cout << &mContext << std::endl;
    mTextEffectTime = sf::Time::Zero;
    mSettingsSprite.setTexture(*getContext().textures->get("icons/settings"));
    mBackgroundSprite.setTexture(*getContext().textures->get("menu/main/background"));
	mOnePlayerSprite.setTexture(*getContext().textures->get("OnePlayer"));
	mTwoPlayersSprite.setTexture(*getContext().textures->get("TwoPlayers"));
	updateRatio();

}

void TitleState::updateRatio() {

    auto screenSize = getContext().window->getSize();

    sf::FloatRect screen(0,0,screenSize.x, screenSize.y) ;

    mView = sf::View(screen);
	auto size = mView.getSize();

	auto bgRect  = mBackgroundSprite.getLocalBounds();
	auto bgScale = std::max(size.x/bgRect.width, size.y/bgRect.height);
    mBackgroundSprite.setOrigin(bgRect.width/2., bgRect.height/2.);
	mBackgroundSprite.setScale(bgScale,bgScale);
	mBackgroundSprite.setPosition(size.x/2., size.y/2.);

	mOnePlayerSprite.setScale(2,2);
	auto OP1rect = mOnePlayerSprite.getLocalBounds();
    mOnePlayerSprite.setOrigin(OP1rect.width/2., OP1rect.height/2.);
	mOnePlayerSprite.setPosition(size.x/3.,size.y/2.);

	mTwoPlayersSprite.setScale(2,2);
	auto TP2rect = mTwoPlayersSprite.getLocalBounds();
    mTwoPlayersSprite.setOrigin(TP2rect.width/2., TP2rect.height/2.);
	mTwoPlayersSprite.setPosition(2*size.x/3.,size.y/2.);

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
				coords_screen.x = event.touch.x;
				coords_screen.y = event.touch.y;
			} else {
				coords_screen.x = event.mouseButton.x;
				coords_screen.y = event.mouseButton.y;
			}

			auto coords = getContext().window->mapPixelToCoords(coords_screen, mView);


			bool is1PButtonPressed = mOnePlayerSprite.getGlobalBounds().contains(coords);

			if(is1PButtonPressed){
				getContext().UDPMode = UDPAgent::Solo;
				requestStackPop();
				requestStackPush(States::Game);
				return true;
			}
			bool is2PButtonPressed = mTwoPlayersSprite.getGlobalBounds().contains(coords);

			if(is2PButtonPressed){
				requestStackPop();
				requestStackPush(States::Connect);
			return true;
			}
			bool isSettingsButtonPressed = mSettingsSprite.getGlobalBounds().contains(coords);

			if(isSettingsButtonPressed){
				requestStackPop();
				requestStackPush(States::Settings);
			return true;
			}
			break;
        }

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                requestStackPop();
            break;

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
