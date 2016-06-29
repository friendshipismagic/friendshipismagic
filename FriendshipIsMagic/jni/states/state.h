#pragma once
#include "../ressources/resourceholder.h"
#include <map>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../network/udp-agent.h"
#include <iostream>

class StateStack;

namespace States
{
    enum ID
    {
		Splash,
        Title,
        Menu,
        Pause,
        Game,
		Settings,
		Connect,
		Waiting,
		End
    };
}

class State
{
    public:

        struct Context
        {
            Context(sf::RenderWindow& win, TextureHolder& textu, FontHolder& fon, SoundBufferHolder& s)
            {
            	std::cout << "contexte initialisé" << std::endl;
                window = &win;
                textures = &textu;
                fonts = &fon;
                sounds = &s;
                UDPMode = UDPAgent::Mode::None;
                foundPlayer = false;

            }

            struct ModeDebug {
            	UDPAgent::Mode UDPMode;
            	ModeDebug& operator=(const UDPAgent::Mode& mode) {
            		std::cout << "switch udp mode from " << UDPMode << " to " << mode << std::endl;
            		this->UDPMode = mode;
            		return *this;
            	}

            	operator UDPAgent::Mode () {
            		return UDPMode;
            	}
            };

            sf::RenderWindow* window;
            TextureHolder* textures;
            FontHolder* fonts;
            SoundBufferHolder* sounds;
            ModeDebug UDPMode;
            bool foundPlayer;

        };

    public:
        State(StateStack& stack, State::Context& context);
        virtual ~State();
        virtual void draw() = 0;
        virtual bool update(sf::Time dt) = 0;
        virtual bool handleEvent(const sf::Event& event) = 0;
        virtual void init() = 0;

    protected:
        void requestStackPush(States::ID stateID);
        void requestStackPop();
        void requestStateClear();
        Context& getContext() const;
        StateStack* mStack;
        Context& mContext;


};
