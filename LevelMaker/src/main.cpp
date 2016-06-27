#include <iostream>
#include <cmath>
#include <limits>
#include <fstream>
#include "tinyxml2.h"
#include <vector>
#include <string>
#include <string>
#include <SFML/Graphics.hpp>
#include <json.h>
#include <cstdio>

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


class GroupVisitor {
    
    public:



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
    
    std::map<MapElement*, std::string> mIdsMissing;


    Map mMap;

    Layer* mCurrentLayer = nullptr;


    public:
        Map&  getMap() {
            return mMap;
        }

    private:
        void ParsePhysicBox(MapElementData* elt, XMLElement* element) {
            if (std::strcmp(element->Name(),"rect")==0) {
                auto x = element->Attribute("x");
                auto y = element->Attribute("y");
                auto width = element->Attribute("width");
                auto height = element->Attribute("height");

                if(x == nullptr || y == nullptr || width == nullptr || height == nullptr) {
                    std::cout << "## ERROR, can't parse rect" << std::endl;
                    return;
                }

                elt->addRect(std::atoi(x),std::atoi(y),std::atoi(width),std::atoi(height));
            }
            else if (std::strcmp(element->Name(), "path")==0) {
                std::cout << "found path" << std::endl;
                std::vector<sf::Vector2f> points;

                auto cpath = element->Attribute("d");

                if (cpath == nullptr) {
                    std::cout << "## ERROR, can't parse path" << std::endl;
                    return;
                }

                std::string path(cpath);

                std::istringstream values (cpath);

                while(!values.eof())
                {
                    sf::Vector2f pos;
                    char comma;
                    values >> pos.x;
                    if (values.fail()) {
                        values.clear();
                        std::string mode;
                        values >> mode;
                        if (mode =="z") break;
                        values >> pos.x >> comma >> pos.y;

                    } else values >> comma >> pos.y;

                    if (values.fail()) {
                        std::cout << "Cant parse path" << std::endl;
                        return;
                    }

                    std::cout << "x:" << pos.x << " y:" << pos.y << std::endl;
                    points.push_back(pos);
                }
                elt->addPolygon(points);

            }



        }

        void CleanupAddition(MapElementData* elt, XMLElement* element) {
                
            if(element == nullptr){
                return;
            }


            for(auto next=element; next!=nullptr; ) {

                std::cout << "parsing " << element->Name() << std::endl;
                
                auto phy = next->Attribute("fim:physics");

                if (phy != nullptr && std::strcmp(phy, "block")==0) {
                    ParsePhysicBox(elt, next);
                    auto previous = next;
                    next=previous->NextSiblingElement();
                    previous->Parent()->DeleteChild(previous);
                    continue;
                } else {
                    if (std::strcmp(next->Name(),"rect")==0) {
                        auto x = next->Attribute("x");
                        auto y = next->Attribute("y");
                        if(x == nullptr || y == nullptr) return;
                        sf::Vector2f pos = elt->getPosition();
                        elt->setPosition({std::min<float>(pos.x,atof(x)), std::min<float>(pos.y,atof(y))});

                    }
                }
                auto child = next->FirstChildElement();
                CleanupAddition(elt,child);
                next=next->NextSiblingElement();

            }

        }

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
                    auto mapElt= new MapElementData(id);
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
                        root->SetAttribute("xmlns:inkscape","http://www.inkscape.org/namespaces/inkscape");
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
                    
                    CleanupAddition(mapElt, root);
                    
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
                auto x = element.FloatAttribute("x");
                auto y = element.FloatAttribute("y");
                
                auto xtr = element.Attribute("transform");
                if(xtr==nullptr) throw std::runtime_error("No transform in use element");

                auto transform = std::string(xtr);

                std::size_t first_parenthesis = transform.find('(');
                auto transformType = transform.substr(0,first_parenthesis);
                std::cout << "Transform type is " << transformType << std::endl;

                if (transformType == "translate") {
                    std::size_t comma_pos = transform.find(',');
                    x += atof(transform.substr(first_parenthesis+1, comma_pos-first_parenthesis-2).c_str());
                    y +=atof(transform.substr(comma_pos+1, transform.size()-1-comma_pos).c_str());
                } 
                else if (transformType == "matrix") {
                    throw std::runtime_error("matrix transform not supported yet");
                }

                if(href == nullptr) return true;

                std::string s_href = href;

                if (href[0] == '#') 
                    s_href = s_href.substr(1);

                auto ref = mIds[s_href];

                auto element = new MapElementRef(x, y);

                if (ref == nullptr) 
                    mIdsMissing.insert({element, href});
                else
                    element->setReferee(ref);

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

    Json::StyledWriter writer;

    std::ofstream stream("res/map.json");
    if(stream)
        stream << writer.write(jmap);

    else std::cout << "ERROR WRITING" << std::endl;


	return 0;
}
