#include "splash-state.h"
#include <iostream>

SplashState::SplashState(StateStack& mystack, Context& context)
: State(mystack, context)
{
}

void SplashState::init()
{
	mSettingsSprite.setTexture(*getContext().textures->get("icons/settings"));
	mBackgroundSprite.setTexture(*getContext().textures->get("menu/main/background"));
	
	updateRatio();
}

void SplashState::updateRatio() {
	
	sf::Vector2<unsigned int> screenSize = getContext().window->getSize();
	//sf::Vector2f screenSize = mView.getSize(); 
	
	sf::FloatRect bgRect = mBackgroundSprite.getLocalBounds();
	mBackgroundSprite.setScale(screenSize.x/bgRect.width, screenSize.y/bgRect.height); 
	
	std::cout << "update ratio" << std::endl;
}

bool SplashState::handleEvent(const sf::Event& event)
{
	
	//auto coords = getContext().window->mapPixelToCoords({x,y}, mView);
	//mBackgroundSprite.getGlobalBounds().contains(coords);
	//event.touch.y
	
	
	switch(event.type) {
		case sf::Event::MouseButtonPressed:
		case sf::Event::TouchBegan:  //event.touch // 
			requestStackPop();
			requestStackPush(States::Title);
		case sf::Event::Closed:
			requestStackPop();
			break;
		default:
			break;
	}
	    return true;
}
bool SplashState::update(sf::Time dt)
{
	
	    return true;
}

void SplashState::draw()
{
	mContext.window->draw(mBackgroundSprite);
	mContext.window->draw(mSettingsSprite);
}
