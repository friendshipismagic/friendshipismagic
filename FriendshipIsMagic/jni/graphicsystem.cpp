#include "graphicsystem.h"

GraphicSystem::GraphicSystem(World* world, State::Context context, PhysicSystem* physics)
: System(world, context)
, mWindow(context.window)
, mSprites()
, mPhysics(physics)
{
    sf::Texture*  t = mContext.textures->get("Background");
    background = new sf::Sprite();
    background->setTexture(*t);
    background->setPosition(-100, 0);

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
    mWindow->draw(*background);

    for(std::pair<const int, sf::Sprite> sprite: mSprites)
    {
        mWindow->draw(sprite.second);
    }
}

void GraphicSystem::setPositionProvider(PositionProvider* pos)
{
    mPositionProvider = pos;
}

void GraphicSystem::insertSprite(int entity, std::string id, float rotation, float w, float h)
{
    sf::Texture* t = mContext.textures->get(id);
    sf::Sprite sprite;
    sprite.setTexture(*t);
    float width = sprite.getTextureRect().width;
    float height = sprite.getTextureRect().height;
    sprite.setOrigin(width/2, height/2);
    sprite.setRotation(rotation);
    sprite.setScale(w/width, h/height);
    sprite.setPosition(-1000,-1000); // the first position needs to be invisible

    mSprites.insert(std::make_pair(entity, sprite));
}

void GraphicSystem::deleteSprite(int entity)
{
    mSprites.erase(entity);
}
