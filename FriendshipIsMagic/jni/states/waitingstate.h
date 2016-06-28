#pragma once
#include <SFML/Graphics.hpp>
#include "state.h"

class WaitingState: public State
{
    private:

        sf::View mView;
        sf::Text mText;
        sf::Font* mFont;

        sf::Sprite mBackgroundSprite;

        void updateRatio();

    public:

        WaitingState(StateStack&, Context&);
        virtual void init();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
};
