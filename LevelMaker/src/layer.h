#pragma once

#include <json.h>
#include <string>

class Layer {

    private :

        std::vector<MapElement*> mElements;

        std::string mName = "layer";

    public:

        Layer(std::string name) {
            mName = name;
        }

        const std::string& getName() const {
            return mName;
        }

        Json::Value getJsonObject() const {
            Json::Value value;
            for(auto element : mElements) {
                value.append(element->getJsonObject());
            }
            return value;
        }

        void addElement(MapElement* group) {
            mElements.push_back(group);
        }

};
