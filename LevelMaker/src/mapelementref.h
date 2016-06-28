#pragma once

#include "mapelement.h"

class MapElementRef : public MapElement {

    private:

        MapElement* mRef;
        sf::Vector2f mPos;

    public:

        std::string getObjectId() const override {
            return mRef->getObjectId();
        }

        MapElement::Type getType() const override {
            return MapElement::Type::REF;
        }

        MapElementRef(float x, float y) :
            mRef (nullptr),
            mPos (x,y){
        }

        void setReferee(MapElement* referee) {
            mRef = referee;
        }

        Json::Value getJsonObject() const {
           auto value = mRef->getJsonObject();
           value["ref"] = getObjectId();
           value["x"] = mPos.x;
           value["y"] = mPos.y;
           return value;
        }

        const MapElement* getReferee() const {
            return mRef;
        }
};
