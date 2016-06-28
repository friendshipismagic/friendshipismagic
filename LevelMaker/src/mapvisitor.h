#pragma once

#include <map>
#include <string>

class XMLElement;

class MapVisitor : public XMLVisitor {

    std::map<std::string, MapElement*> mIds;
    std::map<MapElement*, std::string> mIdsMissing;

    Map mMap;
    Layer* mCurrentLayer = nullptr;


    public:
        Map&  getMap();

    private:
        void ParsePhysicBox(MapElementData* elt, XMLElement* element) override;

        void CleanupAddition(MapElementData* elt, XMLElement* element) override;

        bool VisitEnter(const XMLElement& element, const XMLAttribute* attrs) override;

        bool VisitExit(const XMLElement& element) override;
};
