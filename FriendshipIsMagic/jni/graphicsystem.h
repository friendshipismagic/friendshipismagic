#pragma once
#include <SFML/Graphics.hpp>
#include "system.h"
#include "state.h"
#include "systemprovider.h"
#include "physicsystem.h"

class GraphicSystem : public System
{
    public:

        GraphicSystem(World* world, State::Context context, PhysicSystem* physics);

        virtual void update(sf::Time dt);
        void draw();
        void setPositionProvider(PositionProvider* pos);

        void insertSprite(int entity, std::string id, float rotation, float w, float h);
        void deleteSprite(int entity);

    private:

        sf::RenderWindow* mWindow;
        sf::Sprite* background;

        //Sprite component
        std::map<int, sf::Sprite> mSprites;

        PositionProvider* mPositionProvider;
        PhysicSystem* mPhysics;

};
