#include <iostream>
#include "tinyxml2.h"
#include <vector>
#include <string>
#include <string>
#include <SFML/Graphics.hpp>
#include <json.h>

using namespace tinyxml2;


class MapElement {

    private:

    public:
        enum Type { REF, ELT };

        virtual std::string getObjectId() const =0;


        virtual Type getType() const =0;

        virtual Json::Value getJsonObject() const =0;
};

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

        MapElementRef(MapElement* referee, float x, float y) :
            mRef (referee),
            mPos (x,y){
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

XMLNode *deepCopy( const XMLNode *src, XMLDocument *destDoc )
{
    XMLNode *current = src->ShallowClone( destDoc );
    for( const XMLNode *child=src->FirstChild(); child; child=child->NextSibling() )
    {
        current->InsertEndChild( deepCopy( child, destDoc ) );
    }

    return current;
}


class MapElementData : public MapElement {
    private:
        std::string mObjectId;
        sf::Vector2f mPos;

    public:
        std::string getObjectId() const override{
            return mObjectId;
        }

        MapElement::Type getType() const override {
            return MapElement::Type::ELT;
        }

        MapElementData(std::string objectId, float x, float y) :
            mObjectId(objectId),
            mPos (x,y){
        }

        Json::Value getJsonObject() const {
           auto value = Json::Value();
           value["ref"] = getObjectId();
           value["x"] = mPos.x;
           value["y"] = mPos.y;
           return value;
        }
};


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



class MapVisitor : public XMLVisitor {

    std::map<std::string, MapElement*> mIds;

    Map mMap;

    Layer* mCurrentLayer = nullptr;

    public:
        Map&  getMap() {
            return mMap;
        }

    private:
        bool VisitEnter(const XMLElement& element, const XMLAttribute* attrs) {
            if(std::string(element.Name()) == "g") { // On a trouvé un groupe

                auto id = element.Attribute("id");
                auto mode = element.Attribute("inkscape:groupmode");
                auto label = element.Attribute("inkscape:label");

                if (id == nullptr) return true;
                if (mode != nullptr && label != nullptr && std::strcmp(mode, "layer") == 0 ) {
                    if (mCurrentLayer != nullptr) {
                        std::cout << "Layer in layer, can't handle it." << std::endl;
                    }

                    mCurrentLayer = mMap.addLayer(label);
                    std::cout << "Open layer '" << label << "'" << std::endl;
                    return true;
                } else {
                    if (!id) return true;
                    std::cout << "\tfound group id '" << id << "'" << std::endl;
                    auto mapElt= new MapElementData(id,0,0);
                    mCurrentLayer->addElement(mapElt);
                    mIds[id] = mapElt;

                    XMLDocument document;
                    auto decl = document.NewDeclaration("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>");
                    auto root = document.NewElement("svg");
                        root->SetAttribute("xmlns:dc","http://purl.org/dc/elements/1.1/");
                        root->SetAttribute("xmlns:cc","http://creativecommons.org/ns#");
                        root->SetAttribute("xmlns:rdf","http://www.w3.org/1999/02/22-rdf-syntax-ns#");
                        root->SetAttribute("xmlns:svg","http://www.w3.org/2000/svg");
                        root->SetAttribute("xmlns", "http://www.w3.org/2000/svg");
                        root->SetAttribute("xmlns:xlink","http://www.w3.org/1999/xlink");
                        root->SetAttribute("xmlns:sodipodi","http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd");
                        root->SetAttribute("xmlns:inkscape=","http://www.inkscape.org/namespaces/inkscape");
   //width="210mm"
   //height="297mm"
   //viewBox="0 0 744.09448819 1052.3622047"
   //id="svg2"
                        root->SetAttribute("version","1.1");
   //inkscape:version="0.91 r13725"
   //sodipodi:docname="dessin.svg"
                        document.InsertEndChild(root);
                        // etc
                    

                    root->InsertEndChild(deepCopy(&element, &document));
                    document.SaveFile(std::string("res/" + std::string(id) + ".svg").c_str());

                    return false;
                }
            }
            else if(std::string(element.Name()) == "use") {
                //groups.push_back()
                if(mCurrentLayer == nullptr) {
                    std::cout << "### ELEMENT OUTSIDE, ignoring" << std::endl;
                }
                auto href = element.Attribute("xlink:href");
                auto id = element.Attribute("id");
                if(href == nullptr) return true;

                std::string s_href = href;

                if (href[0] == '#') 
                    s_href = s_href.substr(1);

                auto ref = mIds[s_href];

                if (ref == nullptr) {
                    std::cout << "hoho, problème d'id inexistant" << std::endl;
                    return true;
                }
                auto element = new MapElementRef(ref, 0, 0);

                if(id != nullptr)
                    mIds[id] = element;

                mCurrentLayer->addElement(element);

                std::cout << "\tusing use element " << s_href << std::endl;
                return true;

            }
            return true;
        }

        bool VisitExit(const XMLElement& element) override {
            
            if (std::strcmp(element.Name(), "g") == 0){
                std::cout << "<< quit group " << std::endl;
                auto mode = element.Attribute("inkscape:groupmode");
                auto label = element.Attribute("inkscape:label");

                if (mode != nullptr && label != nullptr) {
                    mCurrentLayer = nullptr;

                    std::cout << "Close layer '" << label << "'" << std::endl;
                } 
            }

            return true;
        }


};

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cout << "Usage : LevelMaker <map.svg>" << std::endl;
        return -1;
    }


	XMLDocument doc;
	doc.LoadFile(argv[1]);

	if(doc.Error()) {
		std::cout << "can't load file" << std::endl;
		return 0;
	}


	auto root = doc.RootElement();

	std::cout << "root is tag " << root->Name() << std::endl;

	MapVisitor visitor;
	doc.Accept(&visitor);

    auto map = visitor.getMap();

    auto jmap = map.getJsonObject();

    std::cout << jmap.toStyledString() <<std::endl;


	return 0;
}
