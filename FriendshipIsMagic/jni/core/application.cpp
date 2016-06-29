#include "application.h"
#include "../states/titlestate.h"
#include "../states/settings-state.h"
#include "../states/gamestate.h"
#include "../states/splash-state.h"
#include "../states/connectstate.h"
#include "../states/waitingstate.h"
#include "../states/endstate.h"

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
	mStateStack.registerState(States::Splash, new SplashState(mStateStack, context));
    mStateStack.registerState(States::Title, new TitleState(mStateStack, context));
    mStateStack.registerState(States::Game, new GameState(mStateStack, context));
    mStateStack.registerState(States::Settings, new SettingsState(mStateStack, context));
    mStateStack.registerState(States::Connect, new ConnectState(mStateStack, context));
    mStateStack.registerState(States::Waiting, new WaitingState(mStateStack, context));
    mStateStack.registerState(States::End, new EndState(mStateStack, context));
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow->pollEvent(event))
    {
        if(event.type == sf::Event::LostFocus || 
                event.type == sf::Event::MouseLeft) {
#ifdef ANDROID_BUILD
            mStateStack.clearStates();
            mPause = true;
            mWindow->close();
            break;
#endif
        }
        else if (event.type == sf::Event::GainedFocus)
            mPause = false;
        mStateStack.handleEvent(event);
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::draw()
{
	#ifdef ANDROID_BUILD
    if (mPause) {
        return;
    }
	#endif
    mWindow->clear();
    mStateStack.draw();
    mWindow->display();
}

int Application::run()
{
    sf::Clock clock;
    sf::Time dt = clock.restart();
    while(!mStateStack.isEmpty() && mWindow->isOpen())
    {
        dt = clock.restart();
        processInput();
        update(dt);
        draw();
    }
    if(mWindow->isOpen()) mWindow->close();
    exit(0); // ANDROID TRICK
    return 0;
}
