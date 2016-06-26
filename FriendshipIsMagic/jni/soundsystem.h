#pragma once
#include "system.h"
#include "state.h"
#include "entity.h"
#include <SFML/Audio.hpp>
#include <list>

class SoundSystem: public System
{
    public:

        SoundSystem(World* world, State::Context& context);
        void update(sf::Time dt);

        void play(std::string soundID);

    private:

        std::list<sf::Sound> mSounds;

};
