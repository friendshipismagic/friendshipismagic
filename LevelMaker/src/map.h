#pragma once

#include <map>
#include <vector>
#include <string>

class MapElement;

class Map{

    private:

        std::vector<Layer*> mLayers;
        std::map<std::string, MapElement*> mIds;

    public:

        Layer* addLayer(std::string name) {
            mLayers.push_back(new Layer(name));
            return mLayers.back();
        }

        virtual ~Map() { /*
            for(auto x : mLayers)
                delete x;
            mLayers.clear(); //*/
        }

        Json::Value getJsonObject() const {
            auto doc = Json::Value();
            auto jlayers = Json::Value();
            for(auto layer : mLayers) {
                jlayers[layer->getName()] = layer->getJsonObject();
            }

            doc["layers"] = jlayers;
            return doc;
        }


};
