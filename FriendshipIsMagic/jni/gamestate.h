#pragma once
#include <SFML/Graphics.hpp>
#include "state.h"
<<<<<<< 709bb08eeb9925d4ab3c56e5c55f79b1d0c32c77
#include "world.hpp"
=======
#include "world.h"
>>>>>>> add method "createEntity" to World, the systems have now acess to this method to create a new Entity

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
