#include "GraphicSystem.h"

GraphicSystem::GraphicSystem(State::Context* context, PhysicSystem* physics)
: mContext(context)
, mWindow(context->window)
, mSprites()
, mPhysics(physics)
{
    sf::Texture* t = context->textures->get("Skeleton");
    sf::Sprite s;
    s.setTexture(*t);
    mSprites.push_back(s);
}

void GraphicSystem::update(sf::Time dt)
{
    for (unsigned int i = 0; i < mSprites.size(); i++)
    {
        mSprites[i].setPosition(mPhysics->getPosition(i));
    }
}

void GraphicSystem::draw()
{
    for(sf::Sprite sprite: mSprites)
    {
        mWindow->draw(sprite);
    }
}

void GraphicSystem::setPositionProvider(PositionProvider* pos)
{
    mPositionProvider = pos;
}
