#pragma once
#include <SFML/Graphics.hpp>
#include "state.h"

class ConnectState: public State
{
    private:

        sf::View mView;

        sf::Font* mFont;

        sf::Sprite mBackgroundSprite;
		sf::Sprite mServerModeSprite;
		sf::Sprite mClientModeSprite;

        void updateRatio();

    public:

        ConnectState(StateStack&, Context&);
        virtual void init();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
};
