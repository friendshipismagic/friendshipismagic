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
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        default:
            break;
    }

    if(event.type == sf::Event::Closed)
        requestStackPop();

    return true;
}

void GameState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key==sf::Keyboard::Escape && isPressed)
    {
        requestStackPop();
    }
    if (key==sf::Keyboard::Right)
    {
        mWorld.setRight(isPressed);
    }
    if (key==sf::Keyboard::Left)
    {
        mWorld.setLeft(isPressed);
    }
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
