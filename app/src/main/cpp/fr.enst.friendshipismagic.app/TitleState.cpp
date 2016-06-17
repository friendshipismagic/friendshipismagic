#include "TitleState.h"

TitleState::TitleState(StateStack& mystack, Context context)
: State(mystack, context)
, mFont()
, mTextEffectTime()
, mText()
, mShowText(true)
{
    mFont = mContext.fonts->get("font");
    mText.setFont(*mFont);
    mText.setPosition(250.,300.);
    mText.setString("press any button");
}

void TitleState::init()
{
    mTextEffectTime = sf::Time::Zero;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Game);
    }
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
    //mContext.window->draw(mBackgroundSprite);
    if (mShowText)
        mContext.window->draw(mText);
}
