#pragma once
#include <SFML/Graphics.hpp>
#include "state.h"
#include "../core/world.h"

class GameState: public State
{
	private:

         sf::Font* mFont;
         sf::Text mText;
         World mWorld;
         sf::View mView;

         void updateRatio();

    public:

        GameState(StateStack&, Context&);
        virtual void init();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
};
