#include "titlestate.h"

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
    mBackgroundSprite.setTexture(*getContext().textures->get("menu/main/background"));
}

void TitleState::init()
{
    mTextEffectTime = sf::Time::Zero;
    mSettingsSprite.setTexture(*getContext().textures->get("icons/settings"));
    
}

bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Game);
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
