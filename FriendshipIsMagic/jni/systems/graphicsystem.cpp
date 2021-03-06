#include "graphicsystem.h"
#include "logicsystem.h"

#include "physicsystem.h"
#include "../core/world.h"


GraphicSystem::GraphicSystem(World* world, State::Context& context, PhysicSystem* physics, LogicSystem* logics)

: System(world, context)
, mWindow(context.window)
, mPhysics(physics)
, mLogics(logics)
, mTimer(sf::seconds(60))
{
    sf::Texture*  t = mContext.textures->get("Background");
    background = new sf::Sprite();
    background->setTexture(*t);
    background->setPosition(-100, 0);
    addToScene(background, 0);
    
    auto font = mContext.fonts->get("font");

    mScore.setString("J1 : " + 0);
    mScore.setFont(*font);

    mCoScore.setString("J2 : " + 0);
    mCoScore.setFont(*font);

    std::string timestr = "Time: " + std::to_string(mTimer.asSeconds());
    mTime.setString(timestr);
    mTime.setFont(*font);

    mScore.setPosition(0, 0);
    mCoScore.setPosition(10, 0);
    mTime.setPosition(20, 0);
}

void GraphicSystem::update(sf::Time dt)
{
    auto size = mContext.window->getDefaultView().getSize();

    mScore.setPosition(50,50);

    auto cs_rect = mCoScore.getGlobalBounds();
    mCoScore.setOrigin(cs_rect.width, 0);
    mCoScore.setPosition(size.x-50.f, 50);


    auto time_rect = mTime.getGlobalBounds();
    mTime.setOrigin(time_rect.width/2, 0);
    mTime.setPosition(size.x/2, 60);



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
    if (mLogics->getLogic(Logic::coChangeDirection))
    {
        mirror(mGameWorld->getCoPlayerID(), -1);
    }

    mTimer -= dt;
    mTime.setString("Time: " + std::to_string((int)mTimer.asSeconds()));
}

void GraphicSystem::draw()
{
    mWindow->draw(*background);

    for(auto layerScene: mScene)
    {
        for(sf::Sprite* sprite: layerScene.second)
        {
            mWindow->draw(*sprite);
        }
    }

    auto view = mWindow->getView();

    mWindow->setView(mWindow->getDefaultView());
  	mWindow->draw(mCoScore);
  	mWindow->draw(mScore);
  	mWindow->draw(mTime);
    mWindow->setView(view);

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

    addToScene(&mSprites[entity], 1);
}

void GraphicSystem::deleteSprite(Entity entity)
{

    if (mSprites.find(entity) != mSprites.end())
    {
        eraseFromScene(&mSprites[entity]);
        mSprites.erase(entity);
    }

    if (mSons.find(entity) != mSons.end())
    {
        mSons.erase(entity);
    }

    if (mFathers.find(entity) != mFathers.end())
    {
        deleteDependency(mFathers[entity], entity);
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
		if (mSons[entityFather].find(entitySon) != mSons[entityFather].end())
			mSons[entityFather].erase(entitySon);

	if (mFathers.find(entitySon) != mFathers.end())
	{
		mFathers.erase(entitySon);
	}
}

void GraphicSystem::addToScene(sf::Sprite* node, int layer)
{
    if (mScene.find(layer) != mScene.end())
        mScene[layer].push_back(node);
    else
    {
        std::vector<sf::Sprite*> layerScene;
        layerScene.push_back(node);
        mScene.insert(std::make_pair(layer, layerScene));
    }
}

void GraphicSystem::eraseFromScene(sf::Sprite* node)
{
    for(unsigned int layer = 0; layer < mScene.size() ;layer++)
    {
        if (mScene.find(layer) != mScene.end())
        {
            auto layerScene = mScene[layer];
            for(unsigned int i = 0; i < layerScene.size(); i++)
            {
                if (layerScene[i] == node)
                    layerScene.erase(layerScene.begin() + i);
            }
            mScene[layer] = layerScene;
        }

    }
}

void GraphicSystem::setScores(int score, int coscore)
{
	mScore.setString("J1 : " + std::to_string(score));
	mCoScore.setString("J2 : " + std::to_string(coscore));
}
