#pragma once
#include <SFML/Graphics.hpp>
#include "state.h"

class EndState: public State
{
    private:

        sf::View mView;

        sf::Font* mFont;
        sf::Text mText;
        sf::Sprite mBackgroundSprite;

        void updateRatio();

    public:

        EndState(StateStack&, Context&);
        virtual void init();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
};

