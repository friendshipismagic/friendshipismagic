#include "graphicsystem.h"
#include "world.h"

GraphicSystem::GraphicSystem(World* world, State::Context context, PhysicSystem* physics, LogicSystem* logics)
: System(world, context)
, mWindow(context.window)
, mSprites()
, mPhysics(physics)
, mLogics(logics)
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
        if (mFathers.find(i) != mFathers.end())
            fatherPos = mPhysics->getPosition(mFathers[i]);
        pos.x += fatherPos.x;
        pos.y += fatherPos.y;
        mSprites[i].setPosition(pos);
    }

    if (mLogics->getLogic(Logic::changeDirection))
    {
        mirror(mGameWorld->getPlayerID(), -1);
    }
}

void GraphicSystem::draw()
{
    mWindow->draw(*background);

    for(auto sprite: mSprites)
    {
        mWindow->draw(sprite.second);
    }
}

void GraphicSystem::setPositionProvider(PositionProvider* pos)
{
    mPositionProvider = pos;
}

void GraphicSystem::insertSprite(Entity entity, std::string id, float rotation, float w, float h)
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

    if(mSprites.find(entity) == mSprites.end())
        mSprites.insert(std::make_pair(entity, sprite));
    else
        mSprites[entity] = sprite;
}

void GraphicSystem::deleteSprite(Entity entity)
{
    if (mSprites.find(entity) != mSprites.end())
        mSprites.erase(entity);

    if (mSons.find(entity) != mSons.end())
    {
        for (Entity entitySon : mSons[entity])
        {
            deleteDependency(entity, entitySon);
        }
    }
    if (mFathers.find(entity) != mFathers.end())
    {
        deleteDependency(mFathers[entity], entity);
        mFathers.erase(entity);
    }
}

void GraphicSystem::setSize(Entity entity, float w, float h)
{
    sf::Sprite sprite = mSprites[entity];
    float width = sprite.getTextureRect().width;
    float height = sprite.getTextureRect().height;
    sprite.setScale(w/width, h/height);
    mSprites[entity] = sprite;
}


void GraphicSystem::mirror(Entity entity, int m)
{
    sf::Sprite sprite = mSprites[entity];
    if (m < 0)
        sprite.scale(-1, 1);
    else
        sprite.scale(1, 1);
    sf::Vector2f pos = sprite.getPosition();
    sprite.setPosition(-pos.x, pos.y);
    mSprites[entity] = sprite;
    mPhysics->mirror(entity);
    if (mSons.find(entity) != mSons.end())
    {
        for (Entity entitySon : mSons[entity])
        {
            mirror(entitySon, m);
        }
    }
}

void GraphicSystem::insertDependency(Entity entityFather, Entity entitySon)
{
    if (mSons.find(entityFather) == mSons.end())
    {
        std::set<Entity> sons;
        sons.insert(entitySon);
        mSons.insert(std::make_pair(entityFather, sons));
    }
    else
        mSons[entityFather].insert(entitySon);

    if (mFathers.find(entitySon) == mFathers.end())
    {
        mFathers.insert(std::make_pair(entitySon, entityFather));
    }
    else
        mFathers[entitySon] = entityFather;
}

void GraphicSystem::deleteDependency(Entity entityFather, Entity entitySon)
{
    if (mSons.find(entityFather) != mSons.end())
        mSons[entityFather].erase(entitySon);

    if (mFathers.find(entitySon) == mFathers.end())
    {
        mFathers.erase(entitySon);
    }
}
