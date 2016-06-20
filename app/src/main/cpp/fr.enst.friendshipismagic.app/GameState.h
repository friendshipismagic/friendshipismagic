#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "World.hpp"

class GameState: public State
{
	private:

         sf::Font* mFont;
         sf::Text mText;
         World mWorld;

    public:

        GameState(StateStack&, Context);
        virtual void init();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
};
