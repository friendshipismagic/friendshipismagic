#include "titlestate.h"
#include <iostream>

TitleState::TitleState(StateStack& mystack, Context context)
: State(mystack, context)
, mFont()
, mTextEffectTime()
, mText()
, mShowText(true)
{
    mFont = context.fonts->get("font");
    mText.setFont(*mFont);

    mText.setPosition(250.,300.);
    mText.setString("press any button");
}

void TitleState::init()
{
    mTextEffectTime = sf::Time::Zero;
    mSettingsSprite.setTexture(*getContext().textures->get("icons/settings"));
    mBackgroundSprite.setTexture(*getContext().textures->get("menu/main/background"));

    updateRatio();
}

void TitleState::updateRatio() {
  
    sf::Vector2<unsigned int> screenSize = getContext().window->getSize();
    //sf::Vector2f screenSize = mView.getSize(); 

    sf::FloatRect bgRect = mBackgroundSprite.getLocalBounds();
    mBackgroundSprite.setScale(screenSize.x/bgRect.width, screenSize.y/bgRect.height); 

    std::cout << "update ratio" << std::endl;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {

    	if(event.key.code == sf::Keyboard::S){
    		std::cout << "S pressed!!!!"<< std::endl;
    		 requestStackPop();
    		 requestStackPush(States::Settings);
    	}else{
        requestStackPop();
        requestStackPush(States::Game);
    	}
    }

    if(event.type == sf::Event::Closed)
        requestStackPop();

    return true;
}

bool TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;
    if (mTextEffectTime >= sf::seconds(0.7f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }
    return true;
}

void TitleState::draw()
{
    mContext.window->draw(mBackgroundSprite);
    mContext.window->draw(mSettingsSprite);
}
