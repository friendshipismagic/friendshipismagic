#include "Bloc.h"
#include <iostream>

Bloc::Bloc(b2World* world, float x, float y, float width, float height, float rotation)
: mPos(sf::Vector2f({x,y}))
, mBody()
{
    b2BodyDef mBodyDef;
	mBodyDef.position.Set(x, y);
	mBodyDef.angle = (rotation);

	b2PolygonShape mBox;
	mBox.SetAsBox(width, height);

	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &mBox;
	mFixtureDef.density = 0.0f;
	mFixtureDef.friction = 0.f;
	mFixtureDef.restitution = 0.f;

	mBody = world->CreateBody(&mBodyDef);
    mBody->CreateFixture(&mFixtureDef);
}

sf::Vector2f Bloc::getPos()
{
    return mPos;
}

void Bloc::setPos(sf::Vector2f pos)
{
    mPos = pos;
}

b2Body* Bloc::getBody()
{
    return mBody;
}
