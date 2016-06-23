#pragma once
#include "resourceholder.h"
#include <map>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class StateStack;

namespace States
{
    enum ID
    {
        Title,
        Menu,
        Pause,
        Game
    };
}

class State
{
    public:

        struct Context
        {
            Context(sf::RenderWindow& win, TextureHolder& textu, FontHolder& fon)
            {
                window = &win;
                textures = &textu;
                fonts = &fon;
                playerID = 0;
                playerWeaponID = 1;
            }

            sf::RenderWindow* window;
            TextureHolder* textures;
            FontHolder* fonts;
            int playerID;
            int playerWeaponID;
        };

    public:
        State(StateStack& stack, State::Context context);
        virtual ~State();
        virtual void draw() = 0;
        virtual bool update(sf::Time dt) = 0;
        virtual bool handleEvent(const sf::Event& event) = 0;
        virtual void init() = 0;

    protected:
        void requestStackPush(States::ID stateID);
        void requestStackPop();
        void requestStateClear();
        Context getContext() const;
        StateStack* mStack;
        Context mContext;
};
