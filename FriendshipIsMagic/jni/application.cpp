#include "application.h"
#include "states/titlestate.h"
#include "states/settings-state.h"
#include "states/gamestate.h"

Application::Application(State::Context& context)
: mStateStack(context)
, mWindow(context.window)
{
    registerStates(context);
    //We start with the Title screen
    mStateStack.pushState(States::Title);


    sf::Event event;

    mStateStack.handleEvent(event);

}

void Application::registerStates(State::Context& context)
{
    mStateStack.registerState(States::Title, new TitleState(mStateStack, context));
    mStateStack.registerState(States::Game, new GameState(mStateStack, context));
    mStateStack.registerState(States::Settings, new SettingsState(mStateStack, context));
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow->pollEvent(event))
    {
        mStateStack.handleEvent(event);
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::draw()
{
    mWindow->clear();
    mStateStack.draw();
    mWindow->display();
}

int Application::run()
{
    sf::Clock clock;
    sf::Time dt = clock.restart();
    while(!mStateStack.isEmpty())
    {
        dt = clock.restart();
        processInput();
        update(dt);
        draw();
    }
    mWindow->close();

    return 0;
}
