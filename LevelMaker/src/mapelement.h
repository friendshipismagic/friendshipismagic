#pragma once

#include <json.h>
#include <string>

class MapElement {

    private:

    public:
        enum Type { REF, ELT };

        virtual std::string getObjectId() const =0;


        virtual Type getType() const =0;

        virtual Json::Value getJsonObject() const =0;
};
