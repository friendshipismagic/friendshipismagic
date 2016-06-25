#include "soundsystem.h"
#include "world.h"

SoundSystem::SoundSystem(World* world, State::Context context)
: System(world, context)
{

}

void SoundSystem::update(sf::Time dt)
{
    mSounds.remove_if([] (const sf::Sound& s)
    {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

void SoundSystem::play(std::string soundID)
{
    mSounds.push_back(sf::Sound(*mContext.sounds->get(soundID)));
    mSounds.back().play();
}

