#pragma once
#include <SFML/Graphics.hpp>
#include "system.h"
#include "state.h"
#include "systemprovider.h"
#include "physicsystem.h"
#include "entity.h"
#include <set>
#include "logicsystem.h"

class GraphicSystem : public System
{
    public:

        GraphicSystem(World* world, State::Context context, PhysicSystem* physics, LogicSystem* logics);

        virtual void update(sf::Time dt);
        void draw();
        void setPositionProvider(PositionProvider* pos);

        void insertSprite(Entity entity, std::string id, float rotation, float w, float h);
        void deleteSprite(Entity entity);

        void insertDependency(Entity entityFather, Entity entitySon);
        void deleteDependency(Entity entityFather, Entity entitySon);

        void setSize(Entity entity, float w , float h);
        void mirror(Entity entity, int m);

    private:

        sf::RenderWindow* mWindow;
        sf::Sprite* background;

        //Sprite component
        std::map<Entity, sf::Sprite> mSprites;

        std::map<Entity, std::set<Entity> > mSons;
        std::map<Entity, Entity> mFathers;

        PositionProvider* mPositionProvider;
        PhysicSystem* mPhysics;
        LogicSystem* mLogics;

};
