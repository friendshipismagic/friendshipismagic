#include "GameState.h"

GameState::GameState(StateStack& mystack, State::Context context)
: State(mystack, context)
, mFont()
, mText()
, mWorld(&context)
{
    mFont = mContext.fonts->get("font");
    mText.setFont(*mFont);
    mText.setPosition(250.,300.);
    mText.setString("GameState! Yeah!");
}

void GameState::init()
{

}

bool GameState::handleEvent(const sf::Event& event)
{
    mWorld.handleEvent(event);

    if(event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            requestStackPop();
        }
    }

    if(event.type == sf::Event::Closed)
        requestStackPop();

    return true;
}

bool GameState::update(sf::Time dt)
{
    mWorld.update(dt);

    return true;
}

void GameState::draw()
{
    mWorld.draw();
}
