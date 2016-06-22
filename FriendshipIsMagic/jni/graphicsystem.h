#pragma once
#include <SFML/Graphics.hpp>
#include "system.h"
#include "state.h"
#include "systemprovider.h"
#include "physicsystem.h"

class GraphicSystem : public System
{
    public:

        GraphicSystem(State::Context* context, PhysicSystem* physics);
        virtual void update(sf::Time dt);
        void draw();
        void setPositionProvider(PositionProvider* pos);

    private:

        State::Context* mContext;
        sf::RenderWindow* mWindow;
        sf::Sprite* background;

        //Sprite component
        std::map<int, sf::Sprite> mSprites;
        void insertSprite(int entity, std::string id, float rotation, float w, float h);

        PositionProvider* mPositionProvider;
        PhysicSystem* mPhysics;

};
