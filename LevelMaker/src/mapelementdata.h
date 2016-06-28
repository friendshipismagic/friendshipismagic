#pragma once

#include <string>
#include <SFML/Graphics/Vector.h>
#include <json.h>

class MapElementData : public MapElement {
    private:
        std::string mObjectId;
        sf::Vector2f mPos;

        std::vector< std::vector<sf::Vector2f> > mPolygons;
        std::vector< sf::FloatRect > mRects;

    public:

        void setPosition(const sf::Vector2f& pos) {
            mPos = pos;
        }

        const sf::Vector2f& getPosition() const {
            return mPos;
        }

        std::string getObjectId() const override{
            return mObjectId;
        }

        MapElement::Type getType() const override {
            return MapElement::Type::ELT;
        }

        MapElementData(std::string objectId) :
            mObjectId(objectId){

            mPos.x = mPos.y = std::numeric_limits<float>::max();

        }

        void addPolygon(const std::vector<sf::Vector2f>& polygon) {
            mPolygons.push_back(polygon);
            std::cout << "add polygon" << std::endl;
        }

        void addRect(float x, float y, float w, float h) {
            mRects.push_back({x,y,w,h});
            std::cout << "add rect" << std::endl;
        }

        Json::Value getJsonObject() const {
            auto value = Json::Value();
            value["ref"] = getObjectId();
            value["x"] = mPos.x;
            value["y"] = mPos.y;

            auto physics = Json::Value();
            for(auto p : mPolygons) {
                auto jpoly = Json::Value();
                jpoly["type"] = "polygon";
                for(auto coords : p) {
                    auto jcoords = Json::Value();
                    jcoords["x"] = coords.x;
                    jcoords["y"] = coords.y;
                    jpoly["points"].append(jcoords);
                }
                physics.append(jpoly);
            }

            for(auto rect : mRects) {
                auto jrect = Json::Value();
                jrect["type"] = "rect";
                auto jcoords = Json::Value();
                jrect["x"] = rect.left;
                jrect["y"] = rect.top;
                jrect["w"] = rect.width;
                jrect["h"] = rect.height;
                physics.append(jrect);
            }

            value["physics"] = physics;

           return value;
        }
};
