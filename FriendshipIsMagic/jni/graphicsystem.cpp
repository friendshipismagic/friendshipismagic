#include "GraphicSystem.h"

GraphicSystem::GraphicSystem(State::Context* context, PhysicSystem* physics)
: mContext(context)
, mWindow(context->window)
, mSprites()
, mPhysics(physics)
{
    sf::Texture*  t = context->textures->get("Background");
    background = new sf::Sprite();
    background->setTexture(*t);
    background->setPosition(-100, 0);

    t = context->textures->get("Skeleton");
    sf::Sprite s;
    s.setTexture(*t);
    mSprites.push_back(s);

    t = context->textures->get("Floor");
    sf::Sprite floor;
    floor.setTexture(*t);
    mSprites.push_back(floor);
    mSprites.push_back(floor);
    mSprites.push_back(floor);
}

void GraphicSystem::update(sf::Time dt)
{
    for (unsigned int i = 0; i < mSprites.size(); i++)
    {
        mSprites[i].setOrigin(mSprites[i].getTextureRect().width/2, mSprites[i].getTextureRect().height/2);
        mSprites[i].setPosition(mPhysics->getPosition(i));
    }
}

void GraphicSystem::draw()
{
    mWindow->draw(*background);

    for(sf::Sprite sprite: mSprites)
    {
        mWindow->draw(sprite);
    }
}

void GraphicSystem::setPositionProvider(PositionProvider* pos)
{
    mPositionProvider = pos;
}
