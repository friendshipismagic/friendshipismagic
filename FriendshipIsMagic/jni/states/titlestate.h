#pragma once
#include <SFML/Graphics.hpp>
#include "state.h"

class TitleState: public State
{
    private:

        sf::View mView;

        sf::Font* mFont;
        sf::Time mTextEffectTime;
        sf::Text mText;
        bool mShowText;

        sf::Sprite mBackgroundSprite;
        sf::Sprite mSettingsSprite;

        void updateRatio();

    public:

        TitleState(StateStack&, Context&);
        virtual void init();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
};
