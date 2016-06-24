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
        sf::Vector2f pos = mPhysics->getPosition(i);
        sf::Vector2f fatherPos({0,0});
        auto dependency = mDependencies.find(i);
        if (dependency != mDependencies.end())
            fatherPos = mPhysics->getPosition(mDependencies[i]);
        pos.x += fatherPos.x;
        pos.y += fatherPos.y;
        //std::cout << pos.x << " " << pos.y << std::endl;
        mSprites[i].setPosition(pos);
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

void GraphicSystem::attachSprite(int entityFather, int entitySon)
{
    mDependencies.insert(std::make_pair(entitySon, entityFather));
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
    if (mDependencies.find(entity) != mDependencies.end())
        mDependencies.erase(entity);
}

void GraphicSystem::setSize(int entity, float w, float h)
{
    sf::Sprite sprite = mSprites[entity];
    float width = sprite.getTextureRect().width;
    float height = sprite.getTextureRect().height;
    sprite.setScale(w/width, h/height);
    mSprites[entity] = sprite;
}
