#pragma once
#include <SFML/Graphics.hpp>
#include "state.h"
#include "../core/world.h"
#include <memory>


class GameState: public State
{
	private:

         sf::Font* mFont;
         sf::Text mText;
         std::unique_ptr<World> mWorld;
         sf::View mView;
         sf::Time mGameTime;

         void updateRatio();

    public:

        GameState(StateStack&, Context&);
        virtual void init();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
};
